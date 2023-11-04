#pragma once
#include <list>
#include <vector>          //add by yuesl
#include<string>
using namespace std;
#include "mysql.h"
#pragma comment(lib,"libmysql.lib")

#define MAX_ERR_LEN   256  //add by yuesl

class CMySql
{
public:
    //CMySql(void);  //update by yuesl
    CMySql(string charEncoding = "gb2312");
    ~CMySql(void);
public:                    //ip,用户名,密码，数据库，端口号
    bool  ConnectMySql(char *host,char *user,char *pass,char *db,short nport = 3306);
    void  DisConnect();
    bool  SelectMySql(char* szSql,int nColumn ,list<string>& lstStr);
    //获得数据库中的表
    bool GetTables(char* szSql,list<string>& lstStr);
    //更新：删除、插入、修改
    bool  UpdateMySql(char* szSql);
 
    //----add by yuesl begin---------------------------------------
#define _in_
#define _out_
#define _in_out_
    using C_CHAR  = const char;
    //连接数据库
    bool ConnectMySql(_in_ C_CHAR *host, _in_  C_CHAR *user,
                      _in_ C_CHAR *pass, _in_ C_CHAR *db,
                      _in_ const short nport,
                      _out_ char (&pErrinfo)[MAX_ERR_LEN]);   //如果连接失败返回错误信息

    //仅限查询数据库，将结果信息返回 lstVecStr 中，list 为数据条数，vector为各个字段数据
    bool SelectMySql(_in_ C_CHAR* szSql, _out_ vector<vector<string>>& lstVecStr,
                     _out_ char (&pErrinfo)[MAX_ERR_LEN]);  //查询失败返回错误信息
    //获取某一个表的列字段信息（返回的是不是表数据，而是列名字）
    bool GetTableColumnName(_in_ string table,   //只需要传表名，而不是sql语句
                            _out_ vector<string>& vecColumn,
                            _out_ char (&pErrinfo)[MAX_ERR_LEN]);

    //----add by yuesl end---------------------------------------
private:
    MYSQL *m_sock;
    MYSQL_RES *m_results;
    MYSQL_ROW m_record;
   
};

