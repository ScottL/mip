#include <my_global.h>
#include <mysql.h>
#include <string.h>

/* mysql host, user, password */
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "rootpass"

/******
Database: databat
Table: users
+----------+--------------+------+-----+---------+-------+
| Field    | Type         | Null | Key | Default | Extra |
+----------+--------------+------+-----+---------+-------+
| fullname | varchar(25)  | YES  |     | NULL    |       |
| username | varchar(25)  | YES  |     | NULL    |       |
| pass     | varchar(25)  | YES  |     | NULL    |       |
| email    | varchar(100) | YES  |     | NULL    |       |
| date     | date         | YES  |     | NULL    |       |
| activity | date         | YES  |     | NULL    |       |
+----------+--------------+------+-----+---------+-------+
******/
/* Change username and email fields to unique, don't allow NULL attributes, 
primary key */

MYSQL *connection;
MYSQL_RES *result;
MYSQL_ROW row;
int num, i;
char *sql_str; //sql query string

/* Adds a user into the database. During registration
    Still need sql injection protection */
int add_user(char *fullname, char *username, char *pass, char *email) {

    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "could not initialize MySQL library\n");
        exit(1);
    } 

    connection = mysql_init(NULL);
    mysql_options(connection, MYSQL_READ_DEFAULT_FILE, "/etc/mysql/my.cnf");
    if (mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, 
                    "databat",0, NULL, 0) == NULL){
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }
    
    sql_str = (char*) malloc(300);
    //fullname, username, password, email, date, activity
    sprintf(sql_str, "INSERT INTO users VALUES('%s', '%s', '%s', '%s', now(), now())",
                    fullname, username, pass, email);
    mysql_query(connection, sql_str);
    free (sql_str);

    mysql_close(connection);
    mysql_library_end();
    return -1;
}


/* check if user exists in the databse */
int check_user(char *username, char *pass, char *email){

    //assuming we're checking against username
    char *record;
    record = (char*) malloc(30);
 
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "could not initialize MySQL library\n");
        exit(1);
    }
    connection = mysql_init(NULL);
    mysql_options(connection, MYSQL_READ_DEFAULT_FILE, "/etc/mysql/my.cnf");
    if (mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, 
                  "databat",0, NULL, 0) == NULL){
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }
    
    mysql_query(connection, "SELECT * FROM users");
    result = mysql_store_result(connection);
    num = mysql_num_fields(result);
    while(row = mysql_fetch_row(result)){
        for(i = 0; i < num; i++){
            /*Some way to check and match records in the table
            against the arguments passed in(the user logging in 
            or something */

            strcpy(record, row[i] ? row[i] : "NULL");
            if(strcmp(record, username) == 0){
                /* There is a match in the table */
            }
        } 
    }


    free (record);
    mysql_free_result(result);
    mysql_close(connection);
    mysql_library_end();
    return -1;
}



/* updates the last date of activity */
int update_user(char *username){ 
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "could not initialize MySQL library\n");
        exit(1);
    } 
    connection = mysql_init(NULL);
    mysql_options(connection, MYSQL_READ_DEFAULT_FILE, "/etc/mysql/my.cnf");
    if (mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, 
                  "databat",0, NULL, 0) == NULL){
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }
    
    sql_str = (char*) malloc(125);
    sprintf(sql_str, "UPDATE users SET activity=now() WHERE username='%s'",
                    username);
    mysql_query(connection, sql_str);
    free(sql_str);


    mysql_close(connection);
    mysql_library_end();
    return -1;
}

