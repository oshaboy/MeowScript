#include "../inc/global.hpp"
#include "../inc/scopes.hpp"

MEOWSCRIPT_SOURCE_FILE

unsigned int MeowScript::global::get_line() {
    if(current_scope()->index == 0) {
        return current_scope()->current_line;
    }
    unsigned int line = 0;
    unsigned int index = current_scope()->index;
    while(index != 0) {
        line += scopes[index].current_line;
        index = scopes[index].parent;
    }
    // line += scopes[index].current_line;
    return line;
}

void MeowScript::global::add_trace(unsigned int line, std::string name,std::string file) {
    call_trace.push(std::make_tuple(line,name,file));
}

bool MeowScript::global::pop_trace() {
    if(!call_trace.empty()) {
        call_trace.pop();
        return true;
    }
    return false;
}

fs::path MeowScript::global::include_parent_path() {
    if(include_path.top().has_parent_path()) {
        return include_path.top().parent_path().string() + std::string(MEOWSCRIPT_DIR_SL);
    }
    return "";
}