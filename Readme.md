# TankBot

Controls my modified [Makeblock Starter Robot Kit](http://store.makeblock.com/starter-robot-kit/). The hardware modifications (currently) include a servo in front to lift/lower the ultrasonic sensor and a 7-segment LED display to show the current option setting when the Setting button on the remote is used or the distance in CM to any object detected by the ultrasonic sensor.

The majority of the work is in wrapping the [Makeblock libraries](https://github.com/Makeblock-official/Makeblock-Libraries) I used. The wrappers are by no means feature complete but they're easier to use and simple to extend.

# License

The code isn't marked for licensing because it's a bit fuzzy. Consider all my code MIT unless Makeblock's license requirements supersede that... They reference GPL2 in some places, mention an unspecified commercial license but wrap GPL2 code, so I'm not sure. So, consider it MIT unless you feel the GPL2 applies.
