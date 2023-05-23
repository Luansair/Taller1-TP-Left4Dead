#include <sstream>
#include "../include/action_dto.h"
#include "../include/action_code.h"

Action::Action(std::uint8_t id) : action_id(id) {

}

ShootAction::ShootAction(std::uint8_t shooting) :
    Action(ActionID::SHOOT),
    shooting(shooting) {
    // Nos ayuda a nosotros por si cometemos algun error al parsear!
    // No comprueba si se agregan mas elementos al enum.
    if (!(this->shooting == ActionState::ON || this->shooting ==
    ActionState::OFF)) {
        std::stringstream error_msg;
        error_msg << "Error: Invalid action state assigment.\n"
                     "Reason: Assigning state = "
                  << shooting <<
                  " to an Action of type Shoot. Supported states are: "
                  << ActionState::ON << " and " << ActionState::OFF <<
                  std::endl;
        throw std::runtime_error(error_msg.str());
    }
}

std::vector<std::int8_t> ShootAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(action_id), static_cast<int8_t>(shooting)};
}



