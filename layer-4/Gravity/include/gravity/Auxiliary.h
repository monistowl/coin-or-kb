//
//  Auxiliary.h
//  Gravity
//
//  Created by Hassan Hijazi on 1/3/18.
//
//
/**
 * @file gravity/Auxiliary.h
 * @brief Base class for auxiliary network objects (generators, loads)
 *
 * Provides a base class for objects attached to network nodes.
 *
 * **aux Class:**
 * - _active: Whether this auxiliary is active in the model
 * - _name: Identifier string
 * - _phases: Set of electrical phases (for power systems)
 *
 * **Phase Support:**
 * - set_phases(str): Parse phase string (e.g., "1,2,3")
 * - has_phase(ph): Check if auxiliary has given phase
 *
 * **Usage in Power Systems:**
 * - Generators attached to buses
 * - Loads at network nodes
 * - Capacitors, transformers, etc.
 *
 * @see gravity/Net.h for network container
 * @see gravity/Node.h for bus/node representation
 */
#ifndef Auxiliary_h
#define Auxiliary_h
//#include <gravity/utils.h>

using namespace std;

namespace gravity {

    set<int> get_phases(string phases);
    
    /** Backbone class for auxiliary objects that can be attached to nodes, e.g., generators. */
    class aux{
    public:
        bool _active;
        string _name;
        set<int> _phases;
        virtual ~aux(){};
        void set_phases(string phases){
            _phases = get_phases(phases);
        }
        bool has_phase(const string& ph) const{
            for(auto ph_i: _phases){
                if("ph"+to_string(ph_i)==ph){
                    return true;
                }
            }
            return false;
        }
    };
};
#endif /* Auxiliary_h */
