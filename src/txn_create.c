#include<dhanda/dhanda.h>
#include<dhanda/txn.h>

int txn_add(dhanda *app, txn *txn)
{
	/*struct txn temp;
	int init_posn, fin_posn, txn_id;
	debug_print("");

	fseek(app->txn_fp, 0, SEEK_END);
	init_posn = ftell(app->txn_fp);
	if (init_posn) {
		fseek(app->txn_fp, -sizeof(*txn), SEEK_END);
		fread(&temp, sizeof(*txn), 1, app->txn_fp);
		txn_id = temp.id;
		txn_id++;
	} else {
		txn_id = 1;
	}

	txn->id = txn_id;

	init_posn = ftell(app->txn_fp);
	fwrite(txn, sizeof(*txn), 1, app->txn_fp);
	fin_posn = ftell(app->txn_fp);




	if (init_posn < fin_posn)
		return 0;
	else
		return -1;
		*/

	char sql[1024];
	char *err = NULL;
	int ret;

	char *cat = created_time(txn->cat);
	char *uat = updated_time(txn->uat);

	sprintf(sql, "INSERT INTO transaction(party_id, amount, type, amount, created_at, updated_at) VALUES('%d','%d', '%d', '%s', '%s', '%s')", txn->party_id,
		txn->amount,
		txn->type,
		txn->desc,
		cat,
		uat);
	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		//app_error_set(app, "Failed to add party");
		return -1;
	}

	//app_success_set(app, "Party added successfully");
      return 0;




}
