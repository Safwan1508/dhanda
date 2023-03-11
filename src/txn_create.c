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

	party_update_amount(app, txn->party_id, txn->amount, txn->type);

	char *cat = created_time(txn->cat);

	sprintf(sql, "INSERT INTO transactions(amount, created_at, type, desc, party_id) VALUES(%d, '%s', %d, '%s', %d)", txn->amount, 
																															cat, 
																															txn->type, 
																															txn->desc, 
																															txn->party_id);
																
	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		//app_error_set(app, "Failed to add transaction");
		return -1;
	}


	txn->id = sqlite3_last_insert_rowid(app->db);

	//app_success_set(app, "Transaction added successfully");
	return 0;


}
