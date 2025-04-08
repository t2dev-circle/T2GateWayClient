#include <iostream>
#include "servant/Communicator.h"
#include "T2TarsObj.h"
#include "util/tc_timeprovider.h"

using namespace std;
using namespace T2App;
using namespace tars;

static bool packLogin(T2TarsRequest &req)
{
    int funcNo = 331100;
    map<string, string> data;

    data["func_no"] = std::to_string(funcNo);
    data["op_branch_no"] = "1000";
    data["op_entrust_way"] = "7";
    data["op_station"] = "127.0.0.1";
    data["input_content"] = "1";
    data["account_content"] = "123456";
    data["content_type"] = "0";
    data["password"] = "111111";
    data["asset_prop"] = "0";

    req.funcNo = funcNo;
    req.seqNo = 1;
    req.data.swap(data);

    return true;
}

static bool packQueryStock(T2TarsRequest &req)
{
    int funcNo = 330300;
    map<string, string> data;

    data["func_no"] = std::to_string(funcNo);
    data["op_branch_no"] = "1000";
    data["op_entrust_way"] = "7";
    data["op_station"] = "127.0.0.1";
    data["stock_code"] = "000001";

    req.funcNo = funcNo;
    req.seqNo = 1;
    req.data.swap(data);

    return true;
}

static bool packQueryAsset(T2TarsRequest &req)
{
    int funcNo = 332255;
    map<string, string> data;

    data["func_no"] = std::to_string(funcNo);
    data["op_branch_no"] = "1000";
    data["op_entrust_way"] = "7";
    data["op_station"] = "127.0.0.1";
    data["client_id"] = "123456";
    data["fund_account"] = "123456";
    data["password"] = "111111";

    req.funcNo = funcNo;
    req.seqNo = 1;
    req.data.swap(data);

    return true;
}

static bool packQueryPosition(T2TarsRequest &req)
{
    int funcNo = 333104;
    map<string, string> data;

    data["func_no"] = std::to_string(funcNo);
    data["op_branch_no"] = "1000";
    data["op_entrust_way"] = "7";
    data["op_station"] = "127.0.0.1";
    data["client_id"] = "123456";
    data["fund_account"] = "123456";
    data["password"] = "111111";

    req.funcNo = funcNo;
    req.seqNo = 1;
    req.data.swap(data);

    return true;
}

int main(int argc,char ** argv)
{
    Communicator comm;

    try
    {
        T2TarsObjPrx prx;
        // .tars文件需要与服务端的保持一致
        // 此处ip+port需要以服务端的为准
        comm.stringToProxy("T2App.T2GateWayServer.T2TarsObj@tcp -h 172.19.16.202 -p 18899 -t 60000", prx);

        try
        {
            time_t begin = TC_TimeProvider::getInstance()->getNowMs();

            int count = 10;
            for (int i = 0; i < count; i++)
            {
                T2TarsRequest req;
                T2TarsResponse rsp;

                packQueryStock(req);

                int ret = prx->invoke(req, rsp);

                cout << i << "|" << "req: " << req.writeToJsonString() << endl;
                cout << i << "|" << "ret: " << ret << "|rsp: "<< rsp.writeToJsonString() << endl;
                cout << "//////////////////////////////////////////////////////////////////////////" << endl;
            }

            time_t end = TC_TimeProvider::getInstance()->getNowMs();
            time_t cost = end - begin;

            cout << "count=" << count << "|" << "time=" << cost << "|" << "speed=" << count / (cost / 1000.0)  << endl;

        }
        catch(exception &ex)
        {
            cerr << "ex:" << ex.what() << endl;
        }
        catch(...)
        {
            cerr << "unknown exception." << endl;
        }
    }
    catch(exception& e)
    {
        cerr << "exception:" << e.what() << endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << endl;
    }

    getchar();

    return 0;
}