
> Functie switch case
---
### SwitchKaas gets _number_ **x** and gives _text_ **result**

#### switch ( **x** )
case ( 1 )
--
**result** is "Dit is case 1"
__
case ( 2 )
--
**result** is "Dit is case 2"
__
default
--
**result** is "Default mate"
__ 


___

> Functie aanroepen
_number_ **retVal** is [ SwitchKaas 1 ]
[ printdown "Return value: " plus **retVal** ]
**retVal** is [ SwitchKaas 2 ]
[ printdown "Return value: " plus **retVal** ]

_number_ **rnd** is [ random 500 ]
**retVal** is [ SwitchKaas **rnd** ]
[ printdown "Return value(random~): " plus **retVal** ]