#include "Visitor.hh"
#include <string>
Visitor::Visitor() {
    size_index1 = -1;
    size_index2 = -1;
    tab_formating = 0;
}

void Visitor::begin(LibertyGroup *group) {
    parseGroup(group);
    if (parse_this_)
        return;
    std::string tabs(tab_formating, ' ');
    std::cout << tabs << group->type();

    // The "name" of a group is stored in params()
    if (group->params() && !group->params()->empty()) {
        std::cout << " (";
        bool first = true;
        for (auto p : *group->params()) {
            if (!first) std::cout << ", ";
            if (p->isFloat())
                std::cout << p->floatValue();
            else
                std::cout << p->stringValue();
            first = false;
        }
        std::cout << ") {";
    }
    else
        std::cout << " () {";
    std::cout << std::endl;
    tab_formating += 2;
}

void Visitor::parseGroup(LibertyGroup *group){
    // Optimization: Store type in a variable to make code cleaner
    const char* type = group->type();

    if (
        // --- CCS Timing (The Main Pruning Targets) ---
        strcmp(type, "output_current_rise") == 0 ||
        strcmp(type, "output_current_fall") == 0 ||
        strcmp(type, "receiver_capacitance1_rise") == 0 ||
        strcmp(type, "receiver_capacitance1_fall") == 0 ||
        strcmp(type, "receiver_capacitance2_rise") == 0 ||
        strcmp(type, "receiver_capacitance2_fall") == 0 ||

        // --- CCS Power (Less common but huge) ---
        strcmp(type, "output_current_power_rise") == 0 ||
        strcmp(type, "output_current_power_fall") == 0 ||

        // --- Signal Integrity / Noise (Crosstalk Data) ---
        strcmp(type, "noise_immunity_high") == 0 ||
        strcmp(type, "noise_immunity_low") == 0 ||
        strcmp(type, "noise_immunity_above_high") == 0 ||
        strcmp(type, "noise_immunity_below_low") == 0 ||
        strcmp(type, "propagated_noise_high") == 0 ||
        strcmp(type, "propagated_noise_low") == 0 ||
        strcmp(type, "steady_state_current_high") == 0 ||
        strcmp(type, "steady_state_current_low") == 0 ||
        strcmp(type, "steady_state_current_tristate") == 0 ||

        // --- CCS Noise (Advanced libraries 65nm and below) ---
        strcmp(type, "ccsn_first_stage") == 0 ||
        strcmp(type, "ccsn_last_stage") == 0 ||
        strcmp(type, "dc_current") == 0 ||

        // --- Templates (Definitions for the tables above) ---
        strcmp(type, "output_current_template") == 0 ||
        strcmp(type, "ccsn_first_stage_template") == 0 ||
        strcmp(type, "ccsn_last_stage_template") == 0 ||
        strcmp(type, "dc_current_template") == 0 ||
        strcmp(type, "noise_lut_template") == 0 ||
        strcmp(type, "propagation_lut_template") == 0
    ) {
        parse_this_ = true;
        group_skip_ = group;
        return;
    }
}

void Visitor::end(LibertyGroup *group) {
    if (parse_this_){
        if (group_skip_ == group)
            parse_this_ = false;
        return;
    }
    tab_formating -= 2;
    std::string tabs(tab_formating, ' ');
    std::cout << tabs << '}' << std::endl;
}


void Visitor::visitAttr(LibertyAttr *attr) {
    if (parse_this_)
        return;

    std::string tabs(tab_formating, ' ');
    if (attr->isComplex()) {
        bool needs_quote = false;
        const char* name = attr->name();

        if (strcmp(name, "values") == 0) { // writing tables
            if (size_index2 != -1 && size_index1 != -1){

                std::cout << tabs << name << " ( "; 
                int csv = size_index2;
                bool first = true;
                for (auto v: *attr->values()) {
                    if (csv == 0){
                        std::cout << '"';
                        csv = size_index2;
                    }
                    if (!first)
                        std::cout << ", ";
                    if (csv == size_index2)
                        std::cout << '"';
                    if (v->isFloat()) {
                        std::cout << v->floatValue();
                    } else {
                        std::cout << v->stringValue();
                    }
                    first = false;
                    csv --;
                }
                std::cout << '"';
                std::cout << ");" << std::endl;
                return;
            }
        }


        if (strncmp(name, "index_", 6) == 0) 
            needs_quote = true;
        else if (strcmp(name, "values") == 0)
            needs_quote = true;
        
        std::cout << tabs << name << " ("; 

        if (needs_quote)
            std::cout << '"';

        bool first = true;
        int size = 0;
        for (auto v : *attr->values()) {
            size ++;
            if (!first)
                std::cout << ", ";
            if (v->isFloat()) {
                std::cout << v->floatValue();
            } else {
                std::cout << v->stringValue();
            }
            first = false;
        }
        if (needs_quote)
            std::cout << '"';
        std::cout << ");" << std::endl;

        if (strcmp(name, "index_1") == 0)  // writing tables
            size_index1 = size;
        else if (strcmp(name,"index_2") == 0)
            size_index2 = size;
        else{
            size_index1 = -1;
            size_index2 = -1;
        }

    } 
    
    else {
        std::cout << tabs << attr->name() << " : ";
        
        auto v = attr->firstValue();
        if (v->isFloat()) {
            std::cout << v->floatValue();
        } 
        else {
            const char* val = v->stringValue();
            const char* name = attr->name();
            bool needs_quote = false;

            if (strchr(val, ',') != nullptr) {
                needs_quote = true;
            }
            else if (strcmp(name, "sdf_cond") == 0) 
                needs_quote = true;
            else if (strcmp(name, "date") == 0) 
                needs_quote = true;
            else if (strcmp(name, "comment") == 0) 
                needs_quote = true;
            else if (strcmp(name, "cell_footprint") == 0) 
                needs_quote = true;
            else if (strcmp(name, "function") == 0) 
                needs_quote = true;
            else if (strcmp(name, "related_pin") == 0) 
                needs_quote = true;
            else if (strcmp(name, "related_pg_pin") == 0) 
                needs_quote = true;
            else if (strcmp(name, "voltage_name") == 0) 
                needs_quote = true;

            if (needs_quote) std::cout << '"' << val << '"';
            else std::cout << val;
        }
        
        std::cout << ";" << std::endl;
    }
}

void Visitor::visitVariable(LibertyVariable *variable) {
    std::cout << "VARIABLE: " << variable->variable()
              << " = " << variable->value() << std::endl;
}

void Visitor::visitDefine(LibertyDefine *define) {
    std::cout << "DEFINE: " << define->name()
              << " type=" << (int)define->valueType()
              << std::endl;
}

bool Visitor::save(LibertyGroup*) { return true; }
bool Visitor::save(LibertyAttr*) { return true; }
bool Visitor::save(LibertyVariable*) { return true; }
