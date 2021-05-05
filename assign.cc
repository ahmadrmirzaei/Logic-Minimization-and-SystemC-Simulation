#include "assign.hh"

ostream& operator<<(ostream &out, const Assign &assign) {
    return assign.print(out);
}

ostream& SOP::print(ostream& out) const {
    out << output->name << "\t\t";
    out << delay << endl;
    for(int i=0; i<value.size(); i++) {
        for(int j=0; j<value[i].size(); j++) {
            if(value[i][j].first) out << "~" << value[i][j].second->name;
            else out << value[i][j].second->name;
            if(j != value[i].size()-1) out << "&";
        }
        if(i != value.size()-1) out << " | ";
    }
    return out;
}

ostream& Condition::print(ostream& out) const {
    out << output->name << "\t\t";
    out << delay << endl;
    out << value[0]->name << "?";
    out << value[1]->name << ":";
    out << value[2]->name;
    return out;    
}