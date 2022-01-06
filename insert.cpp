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
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "\
        "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) " \
        "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "\
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
        "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
        "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    // create a transactional object
    work W(C);
    // execute SQL query
    W.exec(sql);
    W.commit();
    cout <<"Records created successfully!"<<endl;
    
        C.disconnect();
    }catch(const std::exception &e){
        cerr<<"error: "<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}