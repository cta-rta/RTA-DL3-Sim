#include <boost/scoped_ptr.hpp>
#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MysqlDBConnector: public DBConnector {

  public:

    vector<string> queryConstructor(string _dbName, int nrows, double **dataWR);

    int writeRowInDB(int idObs, int idRepo, double *dataWR);
    int writeTransactionInDB(int idObs, int idRepo, double *dataWR);
    int writeRowInDBByString(int idObs, int idRepo, double *dataWR);
    int writeRowInDBBySprintf(int idObs, int idRepo, double *dataWR);
    int writeTransactionInDBByString(int idObs, int idRepo, double *dataWR);
    int writeRowInDBExtQuery(string query);

  private:
    sql::Driver *driver;
    boost::shared_ptr <sql::Connection> con;


}
