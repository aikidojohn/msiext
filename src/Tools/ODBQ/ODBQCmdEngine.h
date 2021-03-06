#pragma once

class ODBQCmdEngine
{
private:
    //! xml results
    AppSecInc::Xml::XmlDocument _xmlresults;
    //! root node of xml results
    MSXML2::IXMLDOMNodePtr _xmlresults_rootnode;
    //! output buffer
    std::wstring output;
public:
    //! command line parameters
    TCLAP::CmdLine _cmd;
	//! remove banner
	TCLAP::SwitchArg _nologo;
	//! suppress SQL statement output to console
	TCLAP::SwitchArg _nosql;
	//! quiet execution, no results output
	TCLAP::SwitchArg _noresults;
    //! connection string
    TCLAP::ValueArg<std::wstring> _connectionstring;
    //! optional database name
    TCLAP::ValueArg<std::wstring> _database;
    //! sql queries
    TCLAP::MultiArg<std::wstring> _sql;
    //! sql file(s) to execute
    TCLAP::MultiArg<std::wstring> _file;
    //! sql type, default - SqlServer
    TCLAP::ValueArg<std::wstring> _type;
    //! optional delimiter
    TCLAP::ValueArg<std::wstring> _delimiter;
    //! optional output filename
    TCLAP::ValueArg<std::wstring> _outputfile;
    //! xml data files to insert
    TCLAP::MultiArg<std::wstring> _datafile;
    //! flatten-only flag, don't execute sql
    TCLAP::SwitchArg _flatten;
    //! raw output flag
    TCLAP::SwitchArg _rawoutput;
public:
    ODBQCmdEngine(int argc, wchar_t * argv[]);
    //! execute per command line args
    void Execute();
private:
	//! get connection string
	std::wstring GetConnectionString();
    //! execute a single query
    void ExecuteSql(const std::wstring& query);
    //! execute a single file
    void ExecuteFile(const std::wstring& file);
    //! execute input from parser
    void Execute(AppSecInc::Databases::ODBC::OdbcParser& parser);
    //! insert a data file
    void InsertDataFile(const std::wstring& file);
};
