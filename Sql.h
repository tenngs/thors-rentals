#pragma once

class Sql
{
private:
    std::string customersCreateStmnt = "CREATE TABLE customers("
                                       "ID                       INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "FIRST_NAME               VARCHAR(50)         NOT NULL,"
                                       "SURNAME                  VARCHAR(50)         NOT NULL,"
                                       "ADDRESS_FIRST_LINE       VARCHAR(150)        NOT NULL,"
                                       "POSTCODE                 VARCHAR(7)          NOT NULL,"
                                       "CITY                     VARCHAR(70)         NOT NULL,"
                                       "EMAIL                    VARCHAR(60)         NOT NULL);";

    std::string ordersCreateStmnt = "CREATE TABLE orders("
                                    "ID                    INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "SALES_REP_ID          INTEGER         NOT NULL,"
                                    "CUSTOMER_ID           INTEGER         NOT NULL,"
                                    "EQUIPMENT_TYPE        INTEGER         NOT NULL,"
                                    "EQUIPMENT_ID          INTEGER         NOT NULL,"
                                    "RENTAL_HOURS          INTEGER         NOT NULL,"
                                    "RENTAL_DAYS           INTEGER         NOT NULL,"
                                    "COST                  DECIMAL(3,2)    NOT NULL,"
                                    "RETURN_DATETIME       TEXT            NOT NULL);";

    std::string staffCreateStmnt = "CREATE TABLE staff("
                                   "ID                       INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "FIRST_NAME               VARCHAR(50)         NOT NULL,"
                                   "SURNAME                  VARCHAR(50)         NOT NULL,"
                                   "ADDRESS_FIRST_LINE       VARCHAR(150)        NOT NULL,"
                                   "POSTCODE                 VARCHAR(7)          NOT NULL,"
                                   "CITY                     VARCHAR(40)         NOT NULL,"
                                   "EMAIL                    VARCHAR(60)         NOT NULL,"
                                   "ROLE                     VARCHAR(30)         NOT NULL,"
                                   "EMPLOYMENT_TYPE          CHAR(1)             NOT NULL,"
                                   "APP_ACCESS               CHAR(1)             NOT NULL,"
                                   "COVID_VACCINATED         CHAR(1)             NOT NULL);";

    std::string customersInsertStmnt = "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL)"
                                       "VALUES ('t', 't', '123 Main Street', '29650', 'UKTown1', 'test@test.com');"
                                       "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL)"
                                       "VALUES ('Rocko', 'Rocdanovic', '123 Main Street', '29650', 'UKTown1', 'rocko@rocs.com');"
                                       "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL)"
                                       "VALUES ('Jenny', 'Jemstein', '456 Side Street', '39650', 'UKTown2', 'jens@jemstein.com');";

    std::string staffInsertStmnt = "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                   "VALUES ('t', 't', '123 Main Street', '29650', 'UKTown1', 'test@test.com', 'tester', '9', '0', '1');"
                                   "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                   "VALUES ('Rocko', 'Rocdanovic', '123 Main Street', '29650', 'UKTown1', 'rocko@rocs.com', 'rocker', '1', '1', '1');"
                                   "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                   "VALUES ('Jenny', 'Jemstein', '456 Side Street', '39650', 'UKTown2', 'jens@jemstein.com', 'jenmeister', '2', '0', 0');";

    std::string customersDropStmnt = "DROP TABLE IF EXISTS customers;";

    std::string ordersDropStmnt = "DROP TABLE IF EXISTS orders;";

    std::string staffDropStmnt = "DROP TABLE IF EXISTS staff;";

public:
    std::string getCreateStmnt(std::string tableName);
    std::string getDropStmnt(std::string tableName);
    std::string getInsertStmnt(std::string tableName);
};