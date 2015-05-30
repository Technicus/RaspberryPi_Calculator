 // http://hackyourmind.org/articles/raspberry-pi-with-a-keypad-matrix
 
 #include <iostream>
 #include <memory>
 
 // Include Rpi-hw headers
 #include <rpi-hw.hpp>
 #include <rpi-hw/time.hpp>
 #include <rpi-hw/keypad/matrix.hpp>
 
 // Use the Rpi-hw namespace
 using namespace rpihw;
 
 class MyApp {
    
 public:
    
    // Define the keymap
    std::vector< uint8_t > keymap = {
      '1', '2', '3', '4', '5', '6',
      '7', '8', '9', '0', 'A', 'B',
      'C', 'D', 'E', 'F', 'G', 'H',
      'I', 'J', 'K', 'L', 'M', 'N',
      'O', 'P', 'Q', 'R', 'S', 'T',
      'U', 'V', 'W', 'X', 'Y', 'Z',
      '1', '2', '3', '4', '5', '6',
      '1', '2', '3', '4', '5', '6',
      '1', '2', '3', '4', '5', '6',
      '1', '2', '3', '4', '5', '6'
   };
    
    /** Constructor method **/
    MyApp() : m_keypad( new keypad::matrix( { 2, 3, 4, 17, 27, 22 },  { 14, 5, 6, 13, 19, 26, 12, 16, 20, 21, keymap ) ) {
       
       keypad::T_EventListener listener = std::bind( &MyApp::eventListener, this, std::placeholders::_1 );
       
       // Add the keypad event listener
       m_keypad->addEventListener( listener );
    }
    
    /** Destructor method **/
    ~MyApp() {}
    
    /** A simple keypad event listener **/
    void eventListener( keypad::base &dev ) {
       
       const std::vector< uint8_t > &keystate = dev.keyState();
       
       for ( uint8_t c : keystate )
          std::cout << (char) c << std::flush;
    }
    
    /** Main loop **/
    void run() {
       
       for ( ;; ) {
          
          /* ... */
       }
    }
    
 private:
    
    //! The keypad instance.
    std::unique_ptr< keypad::matrix > m_keypad;
 };
 
 
 int
 main( int argc, char *args[] ) {
    
    MyApp app;
    
    app.run();
    
    return 0;
 }