# TankBot

Controls my modified [Makeblock Starter Robot Kit](http://store.makeblock.com/starter-robot-kit/). The hardware modifications (currently) include a servo in front to lift/lower the ultrasonic sensor and a 7-segment LED display to show the current option setting when the Setting button on the remote is used or the distance in CM to any object detected by the ultrasonic sensor.

The majority of the work is in wrapping the Makeblock libraries. The [original libraries](https://github.com/Makeblock-official/Makeblock-Libraries) can probably be used without issue but I have modified them and [my fork](https://github.com/sraboy/Makeblock-Libraries) is a submodule here. The wrappers are by no means feature complete but they're easier to use and simple to extend.

# License

My code is MIT except where another license applies. Some of Makeblock's code is CC-BY-3.0 or GPL2.
