# UE4 Core Helpers

This plugins is dedicated to brings some extra tools for UE4 developers.

|                                                                                                       <a href="https://www.buymeacoffee.com/NansUE4" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-green.png" alt="Buy Me A Coffee" height="51" width="217"></a>                                                                                                       |
| :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| I've decided to make all the code I developed for my games free to use and open source.<br> I am a true believer in the mindset that sharing and collaborating makes the world a better place.<br> The thing is: I'm fulltime dedicated to my project and these open source plugins, for coding I need a looooot of coffee, so please, help me to get my drug :stuck_out_tongue_closed_eyes: !! |

## 1. Assertions Macros

These **assertions macros** are pass-throughs for standard [UE4 macros](https://docs.unrealengine.com/en-US/Programming/Assertions/index.html) but throw an exception if `WITH_DEV_AUTOMATION_TESTS` is `true` or if `WITH_GG_TESTS` is defined which allow to **test failures**.

`GNAssertThrowError` global `boolean` var can switch on/off exceptions triggering.

| Core Helpers Assertions | UE4 default assertions | Behavior                                                                                               |
| ----------------------- | ---------------------- | ------------------------------------------------------------------------------------------------------ |
| mycheck                 | check                  | Halts execution if Expression is false                                                                 |
| mycheckf                | checkf                 | Halts execution if Expression is false and outputs FormattedText to the log                            |
| myensureMsgf            | ensureMsgf             | Notifies the crash reporter and outputs FormattedText to the log on the first time Expression is false |

## 2. Contributing and Supporting

I've decided to make all the code I developed for my games free to use and open source.  
I am a true believer in the mindset that sharing and collaborating makes the world a better place.  
I'll be very glad if you decided to help me to follow my dream.

| How?                                                                                                                                                                               |                                                                                         With                                                                                         |
| :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| **Donating**<br> Because I'm an independant developer/creator and for now I don't have<br> any income, I need money to support my daily needs (coffeeeeee).                        | <a href="https://www.buymeacoffee.com/NansUE4" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-green.png" alt="Buy Me A Coffee" height="51" width="217" ></a> |
| **Contributing**<br> You are very welcome if you want to contribute. I explain [here](./CONTRIBUTING.md) in details what<br> is the most comfortable way to me you can contribute. |                                                                         [CONTRIBUTING.md](./CONTRIBUTING.md)                                                                         |
