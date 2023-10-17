// Sqlite3.h: interface for the CSqlite3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLITE3_H__6B98E6CE_8F3B_4230_A6A2_FB8A1CA6BB88__INCLUDED_)
#define AFX_SQLITE3_H__6B98E6CE_8F3B_4230_A6A2_FB8A1CA6BB88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sqlite3.h"



#define LogSqlite3Error(db)        DBG_LOG1("Sqlite3 error: %S", sqlite3_errmsg(db))

int sqlite_query_int_value(sqlite3 *db, cstr_t szSql);

class CSqlite3  
{
public:
    CSqlite3();
    virtual ~CSqlite3();

    int open(cstr_t file);
    void close();

    int exec(cstr_t szSql);

    cstr_t errorMsg();

    int LastInsertRowId() { return (int)sqlite3_last_insert_rowid(m_db); }

public:
    sqlite3            *m_db;

};

class CSqlite3Stmt
{
public:
    CSqlite3Stmt();
    virtual ~CSqlite3Stmt();

    int prepare(CSqlite3 *db, cstr_t szSql);
    int step();
    void reset();
    void finalize();

    int bindText(int nField, cstr_t szText, size_t nLen = -1);
    int bindStaticText(int nField, cstr_t szText, size_t nLen = -1);
    int bindBlob(int nField, void * lpData, int nLen);
    int bindStaticBlob(int nField, const void *lpData, int nLen);

    int bindInt(int nField, int nData);
    int bindInt64(int nField, int64_t nData);

    int getColumnCount();
    cstr_t getColumnName(int nCol);

    int columnInt(int nCol);
    int64_t columnInt64(int nCol);
    void columnText(int nCol, string &strText);
    cstr_t columnText(int nCol);
    void columnBlob(int nCol, string &strData);

public:
    sqlite3             *m_db;
    sqlite3_stmt        *m_stmt;

};

#endif // !defined(AFX_SQLITE3_H__6B98E6CE_8F3B_4230_A6A2_FB8A1CA6BB88__INCLUDED_)
