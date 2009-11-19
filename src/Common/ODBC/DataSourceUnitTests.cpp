#include "StdAfxUnitTests.h"
#include "DataSourceUnitTests.h"

using namespace AppSecInc::Databases::ODBC::ODBCDataSource;
using namespace AppSecInc::Databases::MSSQL;
using namespace AppSecInc::UnitTests::Databases::ODBC;

CPPUNIT_TEST_SUITE_REGISTRATION(ODBCDataSourceUnitTests);

void ODBCDataSourceUnitTests::testGetNoError()
{
	// no error
    try 
    { 
        AppSecInc::Databases::ODBC::ODBCDataSource::GetError(); 
        throw "Expected exception"; 
    }
    catch (std::exception& ex) 
    {
        std::cout << std::endl << "Expected exception: " << ex.what();
    }
}

void ODBCDataSourceUnitTests::testConfigureDataSource()
{
    struct TestData
    {
        LPCWSTR driver;
        LPCWSTR name;
        LPCWSTR attributes;
    };

    TestData testdata[] = 
    {
        { L"SQL Server", L"LocalSQLServer", L"SERVER=localhost,1433;Description=local host dsn;Trusted_Connection=yes;" },
    };

    for (int i = 0; i < ARRAYSIZE(testdata); i++)
    {
        std::wcout << std::endl << L"Data source: " << testdata[i].name;
        std::wstringstream attributes;
        attributes << L"DSN=" << testdata[i].name << L";" << testdata[i].attributes;
        AppSecInc::Databases::ODBC::ODBCDataSource::Configure(ODBC_ADD_DSN, testdata[i].driver, attributes.str());
        //! \todo verify that the DSN exists
        AppSecInc::Databases::ODBC::ODBCDataSource::Configure(ODBC_CONFIG_DSN, testdata[i].driver, attributes.str());
        AppSecInc::Databases::ODBC::ODBCDataSource::Configure(ODBC_REMOVE_DSN, testdata[i].driver, attributes.str());
    }
}

void ODBCDataSourceUnitTests::testConfigureDataSourceError()
{
    struct TestData
    {
        LPCWSTR driver;
        LPCWSTR name;
        LPCWSTR attributes;
        LPCSTR error;
    };

    TestData testdata[] = 
    {
        { 
            L"SQL Server", 
            L"", 
            L"SERVER=localhost,1433;Description=local host dsn;Trusted_Connection=yes;", 
            "Error configuring \"SQL Server\" data source: Native error: 11, Message: Driver's ConfigDSN, ConfigDriver, or ConfigTranslator failed" 
        },
        { 
            L"BogusDriver", 
            L"LocalBogusDriverDSN", 
            L"SERVER=localhost,1433;Description=local host dsn;Trusted_Connection=yes;", 
            "Error configuring \"BogusDriver\" data source: Native error: 6, Message: Component not found in the registry" 
        },
    };

    for (int i = 0; i < ARRAYSIZE(testdata); i++)
    {
        try
        {
            std::wcout << std::endl << L"Data source: " << testdata[i].name;
            std::wstringstream attributes;
            attributes << L"DSN=" << testdata[i].name << L";" << testdata[i].attributes;
            AppSecInc::Databases::ODBC::ODBCDataSource::Configure(ODBC_ADD_DSN, testdata[i].driver, attributes.str());
            throw "Expected exception";
        }
        catch(std::exception& ex)
        {
            std::cout << std::endl << ex.what();
            CPPUNIT_ASSERT(0 == strcmp(ex.what(), testdata[i].error));
        }
    }
}