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

        // create a transactional object
        work W(C);
        // create SQL UPDATE statement
        sql = "UPDATE company SET salary = 25000 WHERE id=1;";
        // execute SQL query
        W.exec(sql);
        W.commit();
        cout <<"Records updated successfully!"<<endl;
        // create SQL SELECT statement
        sql = "SELECT * FROM company;";
        // create a non-transactional object
        nontransaction N(C);
        // execute SQL SELECT query
        result R(N.exec(sql));
        /* List down all the records */
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << "Id = " << c[0].as<int>() << endl;
            cout << "Name = " << c[1].as<string>() << endl;
            cout << "Age = " << c[2].as<int>() << endl;
            cout << "Address = " << c[3].as<string>() << endl;
            cout << "Salary = " << c[4].as<float>() << endl;
        }
        cout << "Operation done successfully" << endl;
        C.disconnect();
    }catch(const std::exception &e){
        cerr<<"error: "<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}