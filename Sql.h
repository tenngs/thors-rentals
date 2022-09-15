#pragma once

class Sql
{
private:
    std::string customersCreate = "CREATE TABLE customers("
                                  "ID                       INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "FIRST_NAME               VARCHAR(50)         NOT NULL,"
                                  "SURNAME                  VARCHAR(50)         NOT NULL,"
                                  "ADDRESS_FIRST_LINE       VARCHAR(150)        NOT NULL,"
                                  "POSTCODE                 VARCHAR(7)          NOT NULL,"
                                  "CITY                     VARCHAR(70)         NOT NULL,"
                                  "EMAIL                    VARCHAR(60)         NOT NULL);";

    std::string customersInsert = "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL) "
                                  "VALUES ('t', 't', '123 Main Street', '29650', 'UKTown1', 'test@test.com'); "
                                  "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL) "
                                  "VALUES ('Rocko', 'Rocdanovic', '123 Main Street', '29650', 'UKTown1', 'rocko@rocs.com'); "
                                  "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL) "
                                  "VALUES ('Jenny', 'Jemstein', '456 Side Street', '39650', 'UKTown2', 'jens@jemstein.com');";

public:
    std::string
    getCustomersCreate();
    std::string getCustomersInsert();
};