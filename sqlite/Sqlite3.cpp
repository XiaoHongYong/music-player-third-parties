// Sqlite3.cpp: implementation of the CSqlite3 class.
//
//////////////////////////////////////////////////////////////////////

#include "../../Utils/Utils.h"
#include "sqlite3.h"
#include "Sqlite3.hpp"


int sqlite_query_int_value(sqlite3 *db, cstr_t szSql)
{
    sqlite3_stmt*    sqlquery;
    int                n, nRet;

    nRet = sqlite3_prepare(db, szSql, -1, &sqlquery, nullptr);
    if (nRet != SQLITE_OK)
    {
        LogSqlite3Error(db);
        return 0;
    }
    nRet = sqlite3_step(sqlquery);
    if (nRet != SQLITE_ROW)
    {
        LogSqlite3Error(db);
        return 0;
    }
    n = sqlite3_column_int(sqlquery, 0);
    sqlite3_finalize(sqlquery);
    return n;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSqlite3::CSqlite3()
{
    m_db = nullptr;
}

CSqlite3::~CSqlite3()
{

}

int CSqlite3::open(cstr_t file)
{
    int        nRet;

    nRet = sqlite3_open(file, &m_db);
    if (nRet != SQLITE_OK)
    {
        ERR_LOG1("open db FAILED: %s", file);
        return ERR_SL_OPEN_DB;
    }

    return ERR_OK;
}

void CSqlite3::close()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

int CSqlite3::exec(cstr_t szSql)
{
    int        nRet;

    nRet = sqlite3_exec(m_db, szSql, nullptr, nullptr, nullptr);
    if (nRet != SQLITE_OK)
    {
#ifdef _UNICODE
        ERR_LOG2("CSqlite3::exec %S, %S", sqlite3_errmsg(m_db), szSql);
#else
        ERR_LOG2("CSqlite3::exec %s, %s", sqlite3_errmsg(m_db), szSql);
#endif
        return ERR_SL_EXE_SQL;
    }

    return ERR_OK;
}

cstr_t CSqlite3::errorMsg()
{
    return sqlite3_errmsg(m_db);
}

//////////////////////////////////////////////////////////////////////////

CSqlite3Stmt::CSqlite3Stmt()
{
    m_db = nullptr;
    m_stmt = nullptr;
}

CSqlite3Stmt::~CSqlite3Stmt()
{
    finalize();
}

int CSqlite3Stmt::prepare(CSqlite3 *db, cstr_t szSql)
{
    int            nRet;

    m_db = db->m_db;

    nRet = sqlite3_prepare(m_db, szSql, -1, &m_stmt, nullptr);
    if (nRet != SQLITE_OK)
    {
#ifdef _UNICODE
        ERR_LOG2("Sqlite3Stmt::prepare %S, %S", sqlite3_errmsg(m_db), szSql);
#else
        ERR_LOG2("Sqlite3Stmt::prepare %s, %s", sqlite3_errmsg(m_db), szSql);
#endif
        return ERR_FALSE;
    }

    return ERR_OK;
}

int CSqlite3Stmt::step()
{
    int            nRet;

    nRet = sqlite3_step(m_stmt);
    if (nRet == SQLITE_ROW)
        return ERR_SL_OK_ROW;
    else if (nRet == SQLITE_DONE)
        return ERR_OK;
    else
    {
        LogSqlite3Error(m_db);
        return ERR_SL_DB_ERR;
    }
}

void CSqlite3Stmt::reset()
{
    sqlite3_reset(m_stmt);
}

void CSqlite3Stmt::finalize()
{
    if (m_stmt)
    {
        sqlite3_finalize(m_stmt);
        m_stmt = nullptr;
        m_db = nullptr;
    }
}

int CSqlite3Stmt::bindText(int nField, cstr_t szText, size_t nLen)
{
    int        nRet;

    nRet = sqlite3_bind_text(m_stmt, nField, szText, (int)nLen, SQLITE_TRANSIENT);
    if (nRet != SQLITE_OK)
    {
        LogSqlite3Error(m_db);
        return ERR_SL_BIND_TXT;
    }

    return ERR_OK;
}

int CSqlite3Stmt::bindStaticText(int nField, cstr_t szText, size_t nLen)
{
    int        nRet;

    nRet = sqlite3_bind_text(m_stmt, nField, szText, (int)nLen, SQLITE_STATIC);
    if (nRet != SQLITE_OK)
    {
        LogSqlite3Error(m_db);
        return ERR_SL_BIND_TXT;
    }

    return ERR_OK;
}

int CSqlite3Stmt::bindBlob(int nField, void * lpData, int nLen)
{
    int        nRet;

    nRet = sqlite3_bind_blob(m_stmt, nField, lpData, nLen, SQLITE_TRANSIENT);
    if (nRet != SQLITE_OK)
    {
        LogSqlite3Error(m_db);
        return ERR_SL_BIND_TXT;
    }

    return ERR_OK;
}

int CSqlite3Stmt::bindStaticBlob(int nField, const void *lpData, int nLen)
{
    int        nRet;

    nRet = sqlite3_bind_blob(m_stmt, nField, lpData, nLen, SQLITE_STATIC);
    if (nRet != SQLITE_OK)
    {
        LogSqlite3Error(m_db);
        return ERR_SL_BIND_TXT;
    }

    return ERR_OK;
}

int CSqlite3Stmt::bindInt(int nField, int nData)
{
    int        nRet;

    nRet = sqlite3_bind_int(m_stmt, nField, nData);
    if (nRet != SQLITE_OK)
    {
        LogSqlite3Error(m_db);
        return ERR_SL_BIND_TXT;
    }

    return ERR_OK;
}

int CSqlite3Stmt::bindInt64(int nField, int64_t nData)
{
    int        nRet;

    nRet = sqlite3_bind_int64(m_stmt, nField, nData);
    if (nRet != SQLITE_OK)
    {
        LogSqlite3Error(m_db);
        return ERR_SL_BIND_TXT;
    }

    return ERR_OK;
}

int CSqlite3Stmt::getColumnCount()
{
    return sqlite3_column_count(m_stmt);
}

cstr_t CSqlite3Stmt::getColumnName(int nCol)
{
    return sqlite3_column_name(m_stmt, nCol);
}

int CSqlite3Stmt::columnInt(int nCol)
{
    return sqlite3_column_int(m_stmt, nCol);
}

int64_t CSqlite3Stmt::columnInt64(int nCol)
{
    return sqlite3_column_int64(m_stmt, nCol);
}

void CSqlite3Stmt::columnText(int nCol, string &strText)
{
    cstr_t    szText = (cstr_t)sqlite3_column_text(m_stmt, nCol);

    if (szText)
        strText = szText;
    else
        strText.resize(0);
}

cstr_t CSqlite3Stmt::columnText(int nCol)
{
    return (cstr_t)sqlite3_column_text(m_stmt, nCol);
}

void CSqlite3Stmt::columnBlob(int nCol, string &strData)
{
    char *szData = (char *)sqlite3_column_blob(m_stmt, nCol);
    int        len = sqlite3_column_bytes(m_stmt, nCol);

    strData.resize(0);
    if (szData)
        strData.append(szData, len);
}
