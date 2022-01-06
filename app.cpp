#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]){
    char * sql;
    
    // create connection
    try{
        connection C("dbname = testdb user = postgres password = @S3ns31; hostaddr = 127.0.0.1 port = 5432");
        if(C.is_open()){
            cout << "Opened database successfully: "<< C.dbname()<<endl;
        }else{
            cout<<"Can't open database"<<endl;
            return 1;
        }
        // create SQL statement
    sql = "CREATE TABLE company (id INT PRIMARY KEY NOT NULL,name TEXT NOT NULL, age INT NOT NULL, address CHAR(50), salary REAL);";
    // create a transactional object
    work W(C);
    // execute SQL query
    W.exec(sql);
    W.commit();
    cout <<"Table created successfully!"<<endl;
    
        C.disconnect();
    }catch(const std::exception &e){
        cerr<<"error: "<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}