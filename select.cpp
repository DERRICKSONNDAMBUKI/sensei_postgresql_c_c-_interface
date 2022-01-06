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
        if (C.is_open()){
            cout << "Open database successfully: " << C.dbname() << endl;
        }else{
            cout << "Can't open database!" <<endl;
        }
        sql = "SELECT * FROM company;";
        // create a non-transactional object
        nontransaction N(C);
        // execute ASQL query
        result R(N.exec(sql));
        // list dwon all records 
        for (
            result::const_iterator c=R.begin(); c!=R.end(); ++c
        ){
            cout << "Id = " << c[0].as<int>() <<endl;
            cout << "Name = " << c[1].as<string>() << endl;
            cout << "Age = " << c[2].as<int>() <<endl;
            cout << "Address = " << c[3].as<string>() <<endl;
            cout << "Salary = " <<c[4].as<float>()<<endl;
        }
        cout << "Operation done successfully!"<<endl;
        C.disconnect();
    }catch (const std::exception &e){
        cerr << e.what() <<std::endl;
    }
}