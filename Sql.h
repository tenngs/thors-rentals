#pragma once
/*
    This class contains all Sqlite statements
    required to operate the system.
    Getters are utilised to retrieve values from
    private variables.
*/

class Sql
{

    /*
        Create table statements.
    */
private:
    const std::string customersCreateStmnt = "CREATE TABLE customers("
                                             "ID                       INTEGER PRIMARY KEY AUTOINCREMENT,"
                                             "FIRST_NAME               VARCHAR(50)         NOT NULL,"
                                             "SURNAME                  VARCHAR(50)         NOT NULL,"
                                             "ADDRESS_FIRST_LINE       VARCHAR(150)        NOT NULL,"
                                             "POSTCODE                 VARCHAR(7)          NOT NULL,"
                                             "CITY                     VARCHAR(70)         NOT NULL,"
                                             "EMAIL                    VARCHAR(60)         NOT NULL);";

    const std::string ordersCreateStmnt = "CREATE TABLE orders("
                                          "ID                    INTEGER PRIMARY KEY AUTOINCREMENT,"
                                          "SALES_REP_ID          INTEGER         NOT NULL,"
                                          "CUSTOMER_ID           INTEGER         NOT NULL,"
                                          "EQUIPMENT_TYPE        INTEGER         NOT NULL,"
                                          "EQUIPMENT_ID          INTEGER         NOT NULL,"
                                          "RENTAL_HOURS          INTEGER         NOT NULL,"
                                          "RENTAL_DAYS           INTEGER         NOT NULL,"
                                          "COST                  DECIMAL(3,2)    NOT NULL,"
                                          "RETURN_DATETIME       TEXT            NOT NULL);";

    const std::string staffCreateStmnt = "CREATE TABLE staff("
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

    const std::string systemAccessCreateStmnt = "CREATE TABLE  system_access("
                                                "ID               INTEGER PRIMARY KEY     AUTOINCREMENT,"
                                                "USERNAME         VACHAR(50)              NOT NULL UNIQUE,"
                                                "PASSWORD         VACHAR(50)              NOT NULL,"
                                                "LOGGED_ON        CHAR(1)                 NOT NULL,"
                                                "STAFF_ID         CHAR(100)               NOT NULL,"
                                                "FOREIGN KEY (staff_id) REFERENCES staff (id) ON UPDATE CASCADE ON DELETE CASCADE);";

    const std::string inventorySkisSBsCreateStmnt = "CREATE TABLE inventory_skis_snowboards("
                                                    "ID                INTEGER PRIMARY KEY AUTOINCREMENT,"
                                                    "MAKE              VARCHAR(50)         NOT NULL,"
                                                    "MODEL             VARCHAR(50)         NOT NULL,"
                                                    "PRICE_HOUR        DECIMAL(2,2)        NOT NULL,"
                                                    "PRICE_DAY         DECIMAL(3,2)        NOT NULL,"
                                                    "EQUIPMENT_TYPE    CHAR(1)                     ,"
                                                    "AVAILABLE         CHAR(1)             NOT NULL);";

    /*
        Insert test data into table statements.
    */
    const std::string customersInsertStmnt = "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL)"
                                             "VALUES ('t', 't', '123 Main Street', '29650', 'UKTown1', 'test@test.com');"

                                             "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL)"
                                             "VALUES ('Rocko', 'Rocdanovic', '123 Main Street', '29650', 'UKTown1', 'rocko@rocs.com');"

                                             "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL)"
                                             "VALUES ('Jenny', 'Jemstein', '456 Side Street', '39650', 'UKTown2', 'jens@jemstein.com');";

    const std::string staffInsertStmnt = "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('t', 't', '123 Main Street', '29650', 'UKTown1', 'test@test.com', 'tester', '9', '0', '1');"

                                         "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('Sally', 'Silverstrom', '123 Main Street', '29650', 'UKTown1', 'salls@salberger.com', 'tester', '9', '1', '1');"

                                         "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('Johnny', 'Jordanovic', '907 Cube Street', '29612', 'UKTown19', 'johnmeister@jonslair.com', 'dev', '9', '1', '1');"

                                         "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('Rocko', 'Rocdanovic', '123 Main Street', '29650', 'UKTown1', 'rocko@rocs.com', 'rocker', '1', '1', '1');"

                                         "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('Jenny', 'Jemstein', '456 Side Street', '39650', 'UKTown2', 'jens@jemstein.com', 'jenmeister', '2', '0', 0');";

    const std::string systemAccessInsertStmnt = "INSERT INTO system_access (USERNAME, PASSWORD, LOGGED_ON, STAFF_ID)"
                                                "VALUES ('t', 't', '0', '1');"

                                                "INSERT INTO system_access (USERNAME, PASSWORD, LOGGED_ON, STAFF_ID)"
                                                "VALUES ('sally.silverstrom', 'sally_rocks', '0', '2');"

                                                "INSERT INTO system_access (USERNAME, PASSWORD, LOGGED_ON, STAFF_ID)"
                                                "VALUES ('johnny.jordanovic', 'johnny_also_rocks', '0', '3');";

    const std::string inventorySkisSBsInsertStmnt = "INSERT INTO inventory_skis_snowboards (MAKE, MODEL, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                    "VALUES ('Burton', 'rad air', '19.00', '99.00', '2', '0');"
                                                    "INSERT INTO inventory_skis_snowboards (MAKE, MODEL, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                    "VALUES ('Voelgel', 'racing', '31.00', '190.50', '1', '1');"
                                                    "INSERT INTO inventory_skis_snowboards (MAKE, MODEL, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                    "VALUES ('Salomon', 'nordic star', '27.00', '170.00', '1', '0');"
                                                    "INSERT INTO inventory_skis_snowboards (MAKE, MODEL, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                    "VALUES ('Switchback', 'ultra cool', '11.50', '69.00', '2', '1');";

    /*
        Drop table statements.
    */
    const std::string customersDropStmnt = "DROP TABLE IF EXISTS customers;";

    const std::string ordersDropStmnt = "DROP TABLE IF EXISTS orders;";

    const std::string staffDropStmnt = "DROP TABLE IF EXISTS staff;";

    const std::string system_accessDropStmnt = "DROP TABLE IF EXISTS system_access;";

    /*
        Statements utilised by functions to interact with the
        application database.
    */
    const std::string addCustomerStmnt = "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL) "
                                         "VALUES (?,?,?,?,?,?);";

    const std::string addSystemAccessStaffStmnt = "INSERT INTO system_access (USERNAME, PASSWORD, LOGGED_ON, STAFF_ID)"
                                                  "VALUES (?,?,?,?);";

    const std::string addSkisSnowboarsStmnt = "INSERT INTO inventory_skis_snowboards (MAKE, MODEL, PRICE_HOUR, PRICE_DAY, AVAILABLE)"
                                              "VALUES (?,?,?,?,?);";

    const std::string addAtvStmnt = "INSERT INTO inventory_atvs (MAKE, MODEL, REG, FUEL_TYPE, PRICE_HOUR, PRICE_DAY, AVAILABLE)"
                                    "VALUES (?,?,?,?,?,?,?);";

    const std::string validateUsernameStmnt = "SELECT username FROM system_access WHERE username = ?";

    const std::string validateUnamePasswordStmnt = "SELECT password FROM system_access WHERE password = ? AND username = ?";

    const std::string updateSystemAccessStaffStmnt = "UPDATE system_access SET LOGGED_ON = 1 WHERE USERNAME = \'";

public:
    const std::string getCreateStmnt(std::string tableName);
    const std::string getDropStmnt(std::string tableName);
    const std::string getInsertStmnt(std::string tableName);
    const std::string getAddCustomerStmnt();
    const std::string getAddStaffStmnt();
    const std::string getAddSkisSnowboardStmnt();
    const std::string getAddAtvStmnt();
    const std::string getValidateUsernameStmnt();
    const std::string getValidateUnamePasswordStmnt();
    const std::string getUpdateSystemAccessStaffStmnt();
};