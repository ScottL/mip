#include <my_global.h>
#include <mysql.h>

int add_user(char *name, char *pwd) {

  //char name[] = "First1 Last2";
  //char pass[] = "testPWD";

  if (mysql_library_init(0, NULL, NULL)) {
    fprintf(stderr, "could not initialize MySQL library\n");
    exit(1);
  }

  MYSQL *conn;
  conn = mysql_init(NULL);
  mysql_options(conn, MYSQL_READ_DEFAULT_FILE, "/etc/mysql/my.cnf");
  mysql_real_connect(conn, "localhost", "root", "rootpass", "databat", 0, NULL, 0);

  //mysql_query(conn, "INSERT INTO writers VALUES(name, pass)");

  /*
  mysql_query(conn, "INSERT INTO users VALUES('Scott Lin', '123')");
  mysql_query(conn, "INSERT INTO users VALUES('Greg Siano', '456')");
  mysql_query(conn, "INSERT INTO users VALUES('First Last', 'pwd')");
  mysql_query(conn, "INSERT INTO users VALUES('first last', 'a1-b2')");
  */

  mysql_close(conn);
  mysql_library_end();

}
