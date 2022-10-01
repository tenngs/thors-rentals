#pragma once
/*
    Contains all Sqlite statements
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
                                          "ID                   INTEGER PRIMARY KEY AUTOINCREMENT,"
                                          "SALES_REP_ID         INTEGER         NOT NULL,"
                                          "CUSTOMER_ID          INTEGER         NOT NULL,"
                                          "EQUIPMENT_TYPE       INTEGER         NOT NULL,"
                                          "EQUIPMENT_ID         INTEGER         NOT NULL,"
                                          "RENTAL_HOURS         INTEGER         NOT NULL,"
                                          "RENTAL_DAYS          INTEGER         NOT NULL,"
                                          "COST                 DECIMAL(3,2)    NOT NULL,"
                                          "RETURN_DATETIME      TEXT            NOT NULL,"
                                          "STATUS               CHAR(1)         NOT NULL);";

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

    const std::string inventoryAtvsCreateStmnt = "CREATE TABLE inventory_atvs("
                                                 "ID                INTEGER PRIMARY KEY AUTOINCREMENT,"
                                                 "MAKE              VARCHAR(50)         NOT NULL,"
                                                 "MODEL             VARCHAR(50)         NOT NULL,"
                                                 "REG               VARCHAR(7)          NOT NULL,"
                                                 "FUEL_TYPE         CHAR(1)             NOT NULL,"
                                                 "PRICE_HOUR        DECIMAL(2,2)        NOT NULL,"
                                                 "PRICE_DAY         DECIMAL(3,2)        NOT NULL,"
                                                 "EQUIPMENT_TYPE    CHAR(1)                     ,"
                                                 "AVAILABLE         CHAR(1)                    );";
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
                                         "VALUES ('Sally', 'Silverstrom', '456 Main Street', '29650', 'UKTown13', 'salls@salberger.com', 'tester', '9', '1', '1');"

                                         "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('Johnny', 'Jordanovic', '907 Cube Street', '29612', 'UKTown19', 'johnmeister@jonslair.com', 'dev', '9', '1', '1');"

                                         "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('Rocko', 'Rocdanovic', '789 Main Street', '29650', 'UKTown11', 'rocko@rocs.com', 'rocker', '1', '1', '1');"

                                         "INSERT INTO staff (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL, ROLE, EMPLOYMENT_TYPE, APP_ACCESS, COVID_VACCINATED)"
                                         "VALUES ('Jenny', 'Jemstein', '456 Side Street', '39650', 'UKTown2', 'jens@jemstein.com', 'jenmeister', '2', '0', '0');";

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

    const std::string inventoryAtvsInsertStmnt = "INSERT INTO inventory_atvs (MAKE, MODEL, REG, FUEL_TYPE, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                 "VALUES ('Honda', 'all terrain', 'X21 2153', 'diesel', '33.50', '220.00', '3', '1');"
                                                 "INSERT INTO inventory_atvs (MAKE, MODEL, REG, FUEL_TYPE, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                 "VALUES ('Polaris', 'arctic', 'Y13 9848', 'petrol', '21.00', '160.00', '3', '0');"
                                                 "INSERT INTO inventory_atvs (MAKE, MODEL, REG, FUEL_TYPE, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                 "VALUES ('Yamaha', 'yammaster', 'M67 8302', 'petrol', '48.50', '350.00', '3', '1');"
                                                 "INSERT INTO inventory_atvs (MAKE, MODEL, REG, FUEL_TYPE, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE) "
                                                 "VALUES ('Can-Am', 'camberstein', 'K23 3492', 'diesel', '37.00', '270.00', '3', '1');";

    /*
        Drop table statements.
    */
    const std::string customersDropStmnt = "DROP TABLE IF EXISTS customers;";

    const std::string ordersDropStmnt = "DROP TABLE IF EXISTS orders;";

    const std::string staffDropStmnt = "DROP TABLE IF EXISTS staff;";

    const std::string system_accessDropStmnt = "DROP TABLE IF EXISTS system_access;";

    const std::string inventorySkisSBsDropStmnt = "DROP TABLE IF EXISTS inventory_skis_snowboards;";

    const std::string inventoryAtvsDropStmnt = "DROP TABLE IF EXISTS inventory_atvs;";

    /*
        Statements utilised by functions to interact with the
        application database.
    */
    const std::string addCustomerStmnt = "INSERT INTO customers (FIRST_NAME, SURNAME, ADDRESS_FIRST_LINE, POSTCODE, CITY, EMAIL) "
                                         "VALUES (?,?,?,?,?,?);";

    const std::string addSystemAccessStaffStmnt = "INSERT INTO system_access (STAFF_ID, USERNAME, PASSWORD, LOGGED_ON)"
                                                  "VALUES (?,?,?,?);";

    const std::string addSkisSnowboarsStmnt = "INSERT INTO inventory_skis_snowboards (MAKE, MODEL, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE)"
                                              "VALUES (?,?,?,?,?,?);";

    const std::string addAtvStmnt = "INSERT INTO inventory_atvs (MAKE, MODEL, REG, FUEL_TYPE, PRICE_HOUR, PRICE_DAY, EQUIPMENT_TYPE, AVAILABLE)"
                                    "VALUES (?,?,?,?,?,?,?,?);";

    const std::string addToOrdersStmnt = "INSERT INTO orders (SALES_REP_ID, CUSTOMER_ID, EQUIPMENT_TYPE, EQUIPMENT_ID, RENTAL_HOURS, RENTAL_DAYS, COST, RETURN_DATETIME, STATUS)"
                                         "VALUES (?,?,?,?,?,?,?,?,?);";

    const std::string validateUsernameStmnt = "SELECT username FROM system_access WHERE username = ?";

    const std::string validateUnamePasswordStmnt = "SELECT password FROM system_access WHERE password = ? AND username = ?";

    const std::string updateSystemAccessStaffStmnt = "UPDATE system_access SET LOGGED_ON = 1 WHERE USERNAME = \'";

    const std::string searchForCustomerIDByNameV1 = "SELECT ID FROM customers WHERE FIRST_NAME = \'";
    const std::string searchForCustomerIDByNameV2 = "\' AND SURNAME = \'";

    const std::string searchForCustomerIDByID = "SELECT ID FROM customers WHERE ID = \'";

    const std::string availableEquipIDsV1 = "SELECT ID from ";
    const std::string availableEquipIDsV2 = " WHERE AVAILABLE = 1 AND EQUIPMENT_TYPE = ";

    const std::string availableEquipV1 = "SELECT * from ";
    const std::string availableEquipV2 = " WHERE AVAILABLE = 1 AND EQUIPMENT_TYPE = ";

    const std::string customerFirstName = "SELECT FIRST_NAME FROM customers WHERE ID = ";

    const std::string customerSurname = "SELECT SURNAME FROM customers WHERE ID = ";

    const std::string atvMake = "SELECT MAKE from inventory_atvs WHERE ID = ";

    const std::string atvModel = "SELECT MODEL from inventory_atvs WHERE ID = ";

    const std::string skisSBsMake = "SELECT MAKE from inventory_skis_snowboards WHERE ID = ";

    const std::string skisSBsModel = "SELECT MODEL from inventory_skis_snowboards WHERE ID = ";

    const std::string salesRepID = "SELECT ID FROM system_access WHERE LOGGED_ON = 1";

    const std::string totalSkis = "SELECT count (*) FROM inventory_skis_snowboards WHERE EQUIPMENT_TYPE = '1';";
    const std::string skisForRent = "SELECT count (*) FROM inventory_skis_snowboards WHERE EQUIPMENT_TYPE = 1 AND AVAILABLE = '1';";

    const std::string totalSnowboards = "SELECT count (*) FROM inventory_skis_snowboards WHERE EQUIPMENT_TYPE = '2';";
    const std::string snowboardsForRent = "SELECT count (*) FROM inventory_skis_snowboards WHERE EQUIPMENT_TYPE = '2' AND AVAILABLE = '1';";

    const std::string totalATVs = "SELECT count(*) FROM inventory_atvs;";
    const std::string ATVsForRent = "SELECT count(*) FROM inventory_atvs WHERE AVAILABLE = '1';";

    const std::string totalCustomers = "SELECT count(*) FROM customers;";
    const std::string totalStaff = "SELECT count(*) FROM staff;";
    const std::string totalAppAccessStaff = "SELECT count(*) FROM system_access;";

    const std::string changeAvailabilityATVs = "UPDATE inventory_atvs SET AVAILABLE = 0 WHERE id = ";

    const std::string changeAvailabilitySkisSBs = "UPDATE inventory_skis_snowboards SET AVAILABLE = 0 WHERE id = ";

    const std::string equipmentTypeOnLoan = "SELECT EQUIPMENT_ID FROM ORDERS WHERE EQUIPMENT_TYPE = ? AND STATUS = 1;";

    const std::string returnDatetime = "SELECT RETURN_DATETIME FROM orders WHERE EQUIPMENT_TYPE = ";

    const std::string equipmentIDsOnLoanType1 = "SELECT EQUIPMENT_ID FROM orders WHERE EQUIPMENT_TYPE = 1 AND STATUS = 1;";
    const std::string equipmentIDsOnLoanType2 = "SELECT EQUIPMENT_ID FROM orders WHERE EQUIPMENT_TYPE = 2 AND STATUS = 1;";
    const std::string equipmentIDsOnLoanType3 = "SELECT EQUIPMENT_ID FROM orders WHERE EQUIPMENT_TYPE = 3 AND STATUS = 1;";

    const std::string ordersSum = "SELECT sum(cost) FROM orders WHERE STATUS = 0;";

    const std::string staffIDs = "SELECT ID FROM staff;";

    const std::string systemAccessStaffIDs = "SELECT ID FROM system_access;";

    /*
    Getters for private variables
    */
public:
    const std::string getCreateStmnt(std::string const &tableName);
    const std::string getDropStmnt(std::string const &tableName);
    const std::string getInsertStmnt(std::string const &tableName);
    const std::string getAddCustomerStmnt();
    const std::string getAddStaffStmnt();
    const std::string getAddSkisSnowboardStmnt();
    const std::string getAddAtvStmnt();
    const std::string getValidateUsernameStmnt();
    const std::string getValidateUnamePasswordStmnt();
    const std::string getUpdateSystemAccessStaffStmnt();
    const std::string getSearchForCustomerIDByNameV1();
    const std::string getSearchForCustomerIDByNameV2();
    const std::string getAvailableEquipIDsV1();
    const std::string getAvailableEquipIDsV2();
    const std::string getAvailableEquipV1();
    const std::string getAvailableEquipV2();
    const std::string getSearchForCustomerIDByID();
    const std::string getCustomerFirstName();
    const std::string getCustomerSurname();
    const std::string getAtvMake();
    const std::string getAtvModel();
    const std::string getSkisSBsMake();
    const std::string getSkisSBsModel();
    const std::string getSalesRepID();
    const std::string getTotalSkis();
    const std::string getSkisForRent();
    const std::string getTotalSBsForRent();
    const std::string getSBsForRent();
    const std::string getTotalAtvs();
    const std::string getATVsForRent();
    const std::string getTotalCustomers();
    const std::string getTotalStaff();
    const std::string getTotalAccessStaff();
    const std::string getChangeAvailabilityATVs();
    const std::string getChangeAvailabilitySkisSBs();
    const std::string getAddToOrders();
    const std::string getEquipmentTypeOnLoan();
    const std::string getReturnDatetime();
    const std::string getEquipmentIDsOnLoan(int type);
    const std::string getOrdersSum();
    const std::string getStaffIDs();
    const std::string getSystemAccessStaffIDs();
};