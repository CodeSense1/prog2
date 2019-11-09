#include <iostream>

#include "queue.hh"

// Implement the member functions of Queue here

// this code contains a lot of bugs...


// Constructor that initializes the attribute cycle_.
// (The other attibutes are initialized in the private part below.)
Queue::Queue(unsigned int cycle)
{
    this->cycle_ = cycle;
    this->vehiclesPassed = 0;
}


// Destructor that deletes all the remaining vehicles from the queue.
Queue::~Queue()
{
    // Destroy linked list
}


// Inserts a vehicle, the register number of which is reg, to the queue.
void Queue::enqueue(string reg)
{

    if (is_green_ && vehiclesPassed <= cycle_) {
        // No need to stop
        vehiclesPassed++;
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;

        return;
    }

    if (first_ == nullptr) {

        first_ = new Vehicle({reg, nullptr});
        last_ = first_;

    } else {
        Vehicle* nextInQueue = new Vehicle({reg, nullptr});
        last_->next = nextInQueue;
        last_ = nextInQueue;
    }

    // this->update();
}

bool Queue::dequeue()
{
    // remove first element in queue
    if (first_ == nullptr) {
        // No vehicles to dequeue
        return false;
    }
    Vehicle* second = first_->next;

    if (second == nullptr) {
        // Only one vehicle

        cout << first_->reg_num << " ";
        delete first_;
        last_->next = nullptr;
        last_ = nullptr;
        first_ = last_;
        return true;
    }

    cout << first_->reg_num << " ";
    delete first_;
    first_ = second;

    return true;
}

// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light()
{
    // TODO: detect if
    // Switch light here
    is_green_ = !is_green_;
    // this->update();
    string lightColor = (is_green_) ? "GREEN" : "RED";
    cout << lightColor << ": ";

    if (is_green_) {

        if (first_ != nullptr) {

            // Dequeue <cycle> amount of elements
            // If there are any vehicles, light will turn back to
            // red even if vehiclesPassed < cycle_
            cout << "Vehicle(s) ";

            for (vehiclesPassed = 0; vehiclesPassed < cycle_; vehiclesPassed++) {
                if (!dequeue()) {
                    break;
                }
            }

            cout << "can go on" << endl;

            this->is_green_ = false;

        } else {
            // light is green and there are no vehicles in queue
            cout << "No vehicles waiting in traffic lights" << endl;
        }

    } else {

        // Light is red and there is vehicles in queue
        if (first_ != nullptr) {
            cout << "Vehicle(s) ";
        } else {
            // Light is red and there are no vehicles in queue
            cout << "No vehicles waiting in traffic lights" << endl;
        }

        vehiclesPassed = 0;
    }
}

void Queue::update()
{

    // use this wisely, it might switch light where you dont wan to
    // DO NOT CALL THIS FROM ENQUEUE- funktion!
    if (!is_green_) {
        // On red light no vehicles should pass
        this->vehiclesPassed = 0;
    }


    // Switcth light back to red when enough vehicles have passed
    if (this->vehiclesPassed >= this->cycle_) {
        this->is_green_ = false;
        this->vehiclesPassed = 0;
    }
}


// Resets the attribute cycle_.
void Queue::reset_cycle(unsigned int cycle)
{
    // Does resetting also reset vehiclesPassed?
    this->cycle_ = cycle;
    // this->update();
}

// Prints the color of traffic light and the register numbers of those
// cars that are waiting in the traffic light queue (if any).
void Queue::print()
{
    this->update();
    string lightColor = (is_green_) ? "GREEN" : "RED";
    cout << lightColor << ": ";

    if (is_green_) {
        // light is green

        if (first_ != nullptr) {
            // there are at least one vehicle

            Vehicle* vehicleInQueue = first_;
            cout << "Vehicle(s) ";

            while (vehicleInQueue != nullptr) {
                cout << vehicleInQueue->reg_num << " ";
                vehicleInQueue = vehicleInQueue->next;
            }
            cout << "are waiting in traffic lights" << endl;
        } else {
            // No vehivles are waiting on green lights
            cout << "No vehicles waiting in traffic lights" << endl;
        }

    } else {
        // LIght is red

        if (first_ != nullptr) {
            // There are vehicles in lights
            Vehicle* vehicleInQueue = first_;
            cout << "Vehicle(s) ";

            while (vehicleInQueue != nullptr) {
                cout << vehicleInQueue->reg_num << " ";
                vehicleInQueue = vehicleInQueue->next;
            }

            cout << "waiting in traffic lights" << endl;

        } else {
            // there are no vehicles waiting on red lights
            cout << "No vehicles waiting in traffic lights" << endl;
        }
    }


}
