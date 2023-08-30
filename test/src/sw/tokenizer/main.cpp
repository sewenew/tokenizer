/**************************************************************************
   Copyright (c) 2023 sewenew

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 *************************************************************************/

#include <unistd.h>
#include <iostream>
#include "sw/tokenizer/tiktoken.h"

int main(int argc, char **argv) {
    int opt = 0;
    std::string tiktoken_conf;
    while ((opt = getopt(argc, argv, "t:")) != -1) {
        switch (opt) {
        case 't':
            tiktoken_conf = optarg;
            break;

        default:
            std::cerr << "unknown command option" << std::endl;
            return -1;
            break;
        }
    }

    try {
        sw::tokenizer::TiktokenFactory tiktoken_factory(tiktoken_conf);
        auto tiktoken = tiktoken_factory.create("cl100k_base");
        if (tiktoken.decode(tiktoken.encode("hello world")) != "hello world") {
            std::cerr << "failed to test tiktoken encode and decode" << std::endl;
            return -1;
        }
    } catch (const sw::tokenizer::Error &e) {
        std::cerr << "failed to do test: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
