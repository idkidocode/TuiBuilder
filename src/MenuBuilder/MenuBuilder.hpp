#pragma once

#include <string>
#include <vector>
#include <functional>

namespace TuiBuilder {
    class MenuBuilder
    {
    public:
        void SetOptions(const std::vector<std::string>& opts);
        void SetActions(const std::vector<std::function<void()>>& act);
        void SetEndChar(const std::string& end);

        void Init();
        void Update();
        void End();

    private:
        std::string endChar = "q";

        std::vector<std::string> options = {};
        std::vector<std::function<void()>> actions = {};
        int choice = 0;
    };
}