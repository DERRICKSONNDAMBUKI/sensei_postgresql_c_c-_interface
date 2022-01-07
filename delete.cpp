#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(){
    char * sql;
    try{
        // create connection
        connection C("dbname = testdb user = postgres password = @S3ns31; hostaddr = 127.0.0.1 port = 5432");
        // check connection
        if(C.is_open()){
            cout << "Opened database successionfully: " << C.dbname() << endl;
        }else{
            cout << "Cant't open database" <<endl;
            return 1;
        }
        // create a transactional object
        work W(C);
        // create SQL DELETE statement
        sql = "DELETE FROM company where id = 2;";
        // execute SQL query
        W.exec(sql);
        W.commit();
        cout << "Record deleted successfully!"<<endl;

        // create a SQL SELECT query
        sql = "SELECT * FROM company;";
        // create a non-transactional object
        nontransaction N(C);
        // execute SQL SELECT query
        result R(N.exec(sql));

        // list down all the records 
        for(result::const_iterator c = R.begin(); c != R.end(); ++c){
            cout << "Id = " << c[0].as<int>() <<endl;
            cout << "Name = " << c[1].as<string>()<<endl;
            cout << "Age = " << c[2].as<int>()<<endl;
            cout << "Address = " << c[3].as<string>() << endl;
            cout << "Salary = " << c[4].as<float>() << endl;
        }
        cout << "Operations doen successfully";
        C.disconnect();
    }catch(const std::exception &e){
        cerr << e.what()<<std::endl;
        return 1;
    }
    return 0;
}