/*
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @file http_url_server_sample.cpp
 * @author: zachma
 * @date 2023-7-10
 */

#include <bcos-boostssl/context/ContextConfig.h>
#include <bcos-boostssl/httpserver/Common.h>
#include <bcos-boostssl/websocket/Common.h>
#include <bcos-boostssl/websocket/WsInitializer.h>
#include <bcos-boostssl/websocket/WsService.h>
#include <bcos-utilities/BoostLog.h>
#include <bcos-utilities/Common.h>
#include <bcos-utilities/ThreadPool.h>
#include <memory>

using namespace bcos;
using namespace bcos::boostssl;
using namespace bcos::boostssl::ws;
using namespace bcos::boostssl::http;
using namespace bcos::boostssl::context;

void usage()
{
    std::cerr << "Usage: http-url-server-sample <host> <port> <disableSSL>\n"
              << "Example:\n"
              << "    ./http-url-server-sample 127.0.0.1 20200 true\n"
              << "    ./http-url-server-sample 127.0.0.1 20200 false\n";
    std::exit(0);
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        usage();
    }

    std::string host = argv[1];
    uint16_t port = atoi(argv[2]);

    std::string disableSsl = "true";

    if (argc > 3)
    {
        disableSsl = argv[3];
    }

    BCOS_LOG(INFO) << LOG_DESC("http-url-server-sample") << LOG_KV("ip", host)
                   << LOG_KV("port", port) << LOG_KV("disableSsl", disableSsl);


    auto config = std::make_shared<WsConfig>();
    config->setModel(WsModel::Server);

    config->setListenIP(host);
    config->setListenPort(port);
    config->setThreadPoolSize(4);
    config->setDisableSsl(0 == disableSsl.compare("true"));
    if (!config->disableSsl())
    {
        auto contextConfig = std::make_shared<ContextConfig>();
        contextConfig->initConfig("./boostssl.ini");
        config->setContextConfig(contextConfig);
    }

    auto wsService = std::make_shared<ws::WsService>("TEST");
    auto wsInitializer = std::make_shared<WsInitializer>();

    wsInitializer->setConfig(config);
    wsInitializer->initWsService(wsService);

    auto server = wsService->httpServer();
    server->setHttpUrlReqHandler(
        [](const HttpRequest _req, std::function<void(bcos::bytes)> _callback) {
            auto reqs = _req.body();
            BCOS_LOG(INFO) << LOG_BADGE(" [Main URL] ===>>>> ") << LOG_KV("url_request", reqs);
            _callback(bcos::bytes(reqs.begin(), reqs.end()));
        });

    server->setHttpReqHandler(
        [](const std::string_view _req, std::function<void(bcos::bytes)> _callback) {
            BCOS_LOG(INFO) << LOG_BADGE(" [Main JSON] ===>>>> ") << LOG_KV("request", _req);
            _callback(bcos::bytes(_req.begin(), _req.end()));
        });
    wsService->start();

    int i = 0;
    while (true)
    {
        BCOS_LOG(INFO) << LOG_BADGE(" [Main] ===>>>> ");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        i++;
    }

    return EXIT_SUCCESS;
}