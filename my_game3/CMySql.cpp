//#include "stdafx.h"
#include "CMySql.h"
#include<QDebug>


CMySql::CMySql(string charEncoding)
{
    /*这个函数用来分配或者初始化一个MYSQL对象，用于连接mysql服务端。
    如果你传入的参数是NULL指针，它将自动为你分配一个MYSQL对象，
    如果这个MYSQL对象是它自动分配的，那么在调用mysql_close的时候，会释放这个对象*/
    m_sock = new MYSQL;
    mysql_init(m_sock);
    //mysql_set_character_set(m_sock, "gb2312"); //gb2312 中华人民共和国简体字标准

    //add by yuesl
    //mysql_set_character_set(m_sock, "utf8");   //Qt下默认的文件字符编码为uft-8 所以此处需要修改
    mysql_set_character_set(m_sock, charEncoding.c_str()==""?"gb2312":charEncoding.c_str());
}


CMySql::~CMySql(void)
{
    if(m_sock) {
        delete m_sock;
        m_sock = NULL;
    }
}

void CMySql::DisConnect()
{
    mysql_close(m_sock);
}

bool CMySql::ConnectMySql(char *host, char *user, char *pass, char *db, short nport)
{
    if (!mysql_real_connect(m_sock, host, user, pass, db, nport, NULL, /*CLIENT_MULTI_STATEMENTS*/0)) {
        //连接错误
        return false;
    }
    return true;
}
 bool  CMySql::GetTables(char* szSql, list<string>& lstStr)
 {
    if(mysql_query(m_sock, szSql)) {
        return false;
    }

    m_results = mysql_store_result(m_sock);
    if(NULL == m_results) {
        return false;
    }
    while (m_record = mysql_fetch_row(m_results)) {
        lstStr.push_back(m_record[0]);
    }
    return true;
 }
bool CMySql::SelectMySql(char* szSql,  int nColumn ,list<string>& lstStr)
{
    //mysql_query() 函数用于向 MySQL 发送并执行 SQL 语句
    if(mysql_query(m_sock, szSql)) {
        return false;
    }

     /*·mysql_store_result 对于成功检索了数据的每个查询(SELECT、SHOW、DESCRIBE、EXPLAIN、CHECK TABLE等)
     返回值:
     . CR_COMMANDS_OUT_OF_SYNC 　　以不恰当的顺序执行了命令。
 　　· CR_OUT_OF_MEMORY 　　内存溢出。
 　　· CR_SERVER_GONE_ERROR 　　MySQL服务器不可用。
 　　· CR_SERVER_LOST 　　在查询过程中，与服务器的连接丢失。
 　　· CR_UNKNOWN_ERROR 　　出现未知错误。*/
    m_results = mysql_store_result(m_sock);
    if(NULL == m_results)return false;

    //获取每行的列数:mysql_field_count
    nColumn = nColumn==0?::mysql_field_count(m_sock):nColumn;


    //遍历表中的下一行，取出内容放入m_record 结果集
    while (m_record = mysql_fetch_row(m_results)) {
        
        for(int i = 0; i < nColumn; i++) {
            if(!m_record[i]) {
                lstStr.push_back("");
            } else {
                lstStr.push_back(m_record[i]);
            }
        }
    }
    return true;
}

 bool  CMySql::UpdateMySql(char* szSql)
 {
    if(!szSql) {
        return false;
    }
    if(mysql_query(m_sock, szSql)) {
        qDebug()<<mysql_error(m_sock);
        return false;
    }
    return true;
 }



//---------add by yuesl begin ------------------------------------------------------------------

 bool CMySql::ConnectMySql(C_CHAR *host,   C_CHAR *user,C_CHAR *pass,  C_CHAR *db,const short nport, char (&pErrinfo)[MAX_ERR_LEN]){
     if (!mysql_real_connect(m_sock, host, user, pass, db, nport, NULL, /*CLIENT_MULTI_STATEMENTS*/0)) {
         //连接错误
         strncpy_s(pErrinfo,MAX_ERR_LEN,mysql_error(m_sock),MAX_ERR_LEN-1); //最大截取MAX_ERR_LEN-1长度的错误信息
         return false;
     }
     return true;
 }

//查询功能
 bool CMySql::SelectMySql(C_CHAR* szSql,  vector<vector<string>>& vecVecStr,char (&pErrinfo)[MAX_ERR_LEN])
 {
     if(mysql_query(m_sock, szSql)) { //mysql_query() 函数用于向 MySQL 发送并执行 SQL 语句
         //执行失败，返回错误信息
         strncpy_s(pErrinfo,MAX_ERR_LEN,mysql_error(m_sock),MAX_ERR_LEN-1);
         return false;
     }

     /*·mysql_store_result 对于成功检索了数据的每个查询(SELECT、SHOW、DESCRIBE、EXPLAIN、CHECK TABLE等)
      返回值:
      . CR_COMMANDS_OUT_OF_SYNC 　　以不恰当的顺序执行了命令。
      · CR_OUT_OF_MEMORY 　　       内存溢出。
      · CR_SERVER_GONE_ERROR 　　   MySQL服务器不可用。
      · CR_SERVER_LOST 　　         在查询过程中，与服务器的连接丢失。
      · CR_UNKNOWN_ERROR 　　       出现未知错误。
     */

     m_results = mysql_store_result(m_sock);  //获取结果集
     if(nullptr == m_results)return false;

     //获取表数据的列数
     size_t nColumn = mysql_field_count(m_sock);

     //遍历表中的下一行，取出内容放入m_record 结果集
     while (m_record = mysql_fetch_row(m_results)) {
         vector<string> oneRowData(nColumn);  //存储每一行数据
         for(int i = 0; i < nColumn; i++) {
             oneRowData[i] = m_record[i];
         }
         vecVecStr.push_back(oneRowData);  //添加每行数据
     }
     return true;
 }

 bool CMySql::GetTableColumnName(string table,vector<string>& vecColumn,char (&pErrinfo)[MAX_ERR_LEN]){
     if(table ==""){
         //参数为空
         strncpy_s(pErrinfo,MAX_ERR_LEN,"表名为空",MAX_ERR_LEN-1);
         return false;
     }

     //mysql_query: 查询成功返回0
     return !::mysql_query(m_sock, (string("select *from ")+table).c_str())?[&,this]()->bool{



        //if (  MYSQL_RES* res = nullptr; res = mysql_store_result(m_sock)) { //这个语法需要c++17标准支持，5.6.2版本的Qt不支持

        MYSQL_RES* res = nullptr;
        if ( res = mysql_store_result(m_sock)) {//获得sql语句结束后返回的结果集
            //获取字段数量
            size_t columNum = ::mysql_field_count(m_sock);

            for (int i = 0; i < columNum;i++){ //在已知字段数量的情况下获取字段名
                vecColumn.push_back( mysql_fetch_field(res)->name);
            }
            return true;
        }
        strncpy_s(pErrinfo,MAX_ERR_LEN,mysql_error(m_sock),MAX_ERR_LEN-1);
        return false;

     }(): (strncpy_s(pErrinfo,MAX_ERR_LEN,mysql_error(m_sock),MAX_ERR_LEN-1),false);
 }
