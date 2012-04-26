#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{

  //pointer to mysql structure
  MYSQL *conn;

  conn = mysql_init(NULL); 
  mysql_options(conn, MYSQL_READ_DEFAULT_FILE, "/etc/mysql/my.cnf");

  //connection handler
  if (conn == NULL) {
      printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
      exit(1);
  }
  
  //establish connection to database
  if (mysql_real_connect(conn, "localhost", "root", 
          "rootpass", NULL, 0, NULL, 0) == NULL) {
      printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
      exit(1);
  }

  if (mysql_query(conn, "create database databat")) {
      printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
      exit(1);
  }


  mysql_close(conn);

}
