# Sensei PostgreSQL - C/C++ interface

### Installation
The the latest version of libpqxx is available to be downloaded from the link Download Libpqxx . So download the latest version and follow the following steps − 

Update the package index:
```
# sudo apt-get update
```
Install libpqxx-dev deb package:
```
# sudo apt-get install libpqxx-dev
```
Before you start using C/C++ PostgreSQL interface, find the pg_hba.conf file in your
PostgreSQL installation directory and add the following line −
```
# IPv4 local connections:
host    all     all     127.0.0.1/32    md5
```
#### libpqxx library
- is the official C++ client API for PostgreSQL.

#### API & Description
##### pqxx::connection C( const std::string & dbstring )
This is a typedef which will be used to connect to the database. Here, dbstring provides required parameters to connect to the datbase, for example dbname = testdb user = postgres password=pass123 hostaddr=127.0.0.1 port=5432. If connection is setup successfully then it creates C with connection object which provides various useful function public function.
##### C.is_open()
The method is_open() is a public method of connection object and returns boolean
value. If connection is active, then this method returns true otherwise it returns
false.
##### C.disconnect()
This method is used to disconnect an opened database connection.
##### pqxx::work W( C )
This is a typedef which will be used to create a transactional object using
connection C, which ultimately will be used to execute SQL statements in transactional mode. If transaction object gets created successfully, then it is assigned to variable W which will be used to access public methods related to transactional object.
##### W.exec(const std::string & sql)
This public method from transactional object will be used to execute SQL
statement.
##### W.commit()
This public method from transactional object will be used to commit the transaction.
##### W.abort()
This public method from transactional object will be used to rollback the
transaction.
##### pqxx::nontransaction N( C )
This is a typedef which will be used to create a non-transactional object using
connection C, which ultimately will be used to execute SQL statements in non-
transactional mode. If transaction object gets created successfully, then it is assigned to variable N which will be used to access public methods related to non-transactional object.
##### N.exec(const std::string & sql)
This public method from non-transactional object will be used to execute SQL
statement and returns a result object which is actually an interator holding all the
returned records.

### Compiling and Running
```
$g++ test.cpp -lpqxx -lpq
$./a.out
Opened database successfully: testdb
```