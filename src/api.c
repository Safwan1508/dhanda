#ifndef TERMINAL_APP

#include <kore/kore.h>
#include <kore/http.h>

#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/txn.h>

#include <kore/seccomp.h>

KORE_SECCOMP_FILTER("app",
    KORE_SYSCALL_ALLOW(fsync),
    KORE_SYSCALL_ALLOW(newfstatat),
)


static dhanda app = {};
int api_party_add(struct http_request *req);

void init_app(void)
{
	dhanda_init_app(&app);
}
void party_struct_to_korejson(struct party *p, struct kore_json *json)
{
	struct kore_json_item *item;

	json->root = kore_json_create_object(NULL, NULL);

	item = kore_json_create_integer(json->root, "id", p->id);
	item = kore_json_create_string(json->root, "first_name", p->fname);
	item = kore_json_create_string(json->root, "last_name", p->lname);
	item = kore_json_create_string(json->root, "phone", p->phone);
	item = kore_json_create_integer(json->root, "amount", p->amount);
	item = kore_json_create_integer_u64(json->root, "created_at", p->cat);
	item = kore_json_create_integer_u64(json->root, "updated_at", p->uat);
}

int
api_party_add(struct http_request *req)
{
    struct kore_json json;
	struct kore_json_item *item;
	struct kore_json_item *res_json = NULL;
	struct party p = {};

	kore_json_init(&json, req->http_body->data, req->http_body->length);

	if (!kore_json_parse(&json)) {
		http_response(req, 400, NULL, 0);
		goto cleanup;
	}

	item = kore_json_find_string(json.root, "first_name");
	fprintf(stderr, "First Name: %s\n", item->data.string);
	strcpy(p.fname, item->data.string);
 
	item = kore_json_find_string(json.root, "last_name");
	fprintf(stderr, "Last Name: %s\n", item->data.string);
	strcpy(p.lname, item->data.string);

	item = kore_json_find_string(json.root, "phone");
	fprintf(stderr, "Phone: %s\n", item->data.string);
	strcpy(p.phone, item->data.string);

	item = kore_json_find_integer(json.root, "amount");
	fprintf(stderr, "Amount: %d\n", (int) item->data.u64);

	p.amount = (int) item->data.u64;
 	party_add(&app, &p);

	

	struct kore_buf buf;
	party_struct_to_korejson(&p, &json);

	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(res_json, &buf);

	http_response_headeer(req, "content-type", "application/json");
	http_response(req, 201, buf.data, buf.offset);

	http_response(req, 200, "", 0);

cleanup:
	kore_json_cleanup(&json);

	return KORE_RESULT_OK;
}

int
api_txn_add(struct http_request *req)
{
    struct kore_json json;
	struct kore_json_item *item;
	struct txn t = {};

	kore_json_init(&json, req->http_body->data, req->http_body->length);

	if (!kore_json_parse(&json)) {
		http_response(req, 400, NULL, 0);
		goto cleanup;
	}

	item = kore_json_find_string(json.root, "party_id");
	fprintf(stderr, "PARTYY ID : %s\n", item->data.string);
	strcpy(t.party_id, item->data.string);
 
	item = kore_json_find_string(json.root, "amount");
	fprintf(stderr, "Amount: %d\n", (int) item->data.u64);
	strcpy(t.amount, item->data.string);
	t.amount = (int) item->data.u64;

	item = kore_json_find_string(json.root, "type");
	fprintf(stderr, "TYPE: %s\n", item->data.string);
	strcpy(t.type, item->data.string);

	item = kore_json_find_integer(json.root, "desc");
	fprintf(stderr, "DESC: %d\n", (int) item->data.u64);

	
 	txn_add(&app, &t);
	t.cat = t.uat = time(NULL);

	http_response(req, 200, "", 0);

cleanup:
	kore_json_cleanup(&json);

	return KORE_RESULT_OK;
}

#endif // TERMINAL_APP