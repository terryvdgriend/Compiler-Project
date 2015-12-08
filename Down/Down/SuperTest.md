
> Print 1 t/m # w/e om te testen of alles nog werkt ;)

[ printdown 1 ]


---
### Loopy gets _number_ **x** and gives _number_ **result**
    #### for ( _number_ **i** is 3 , **i** smaller than **x** , **i** is **i** plus 1 )
    --
        [ printdown **i** ]
    __
    **result** is **x** 
___


[ printdown 2 ]


---
    ### Switchy gets _number_ **xx** and gives _number_ **result2**
    
    #### switch ( **xx** )
    case ( 1 )
    --
        **result2** is 1337
    __
    case ( 2 )
    --
        **result2** is 10
    __
	    case ( 16 )
    --
        **result2** is 32
    __
    default
    --
        **result2** is 2337
    __ 
___

_number_ **retVal** is [ Loopy 8 plus 8 ]
[ printdown **retVal** ]
[ printdown 9 ]
**retVal** is [ Switchy 2 ]
[ printdown **retVal** ]



---
### Calcy gets _number_ **age** and gives _number_ **result** 
**age** is **age** plus 1
**result**is**age**
___
[printdown[Calcy[Calcy[Calcy 1]]]]
_number_ **age**

>Bubble Sort

_number_ **size** is 7
_number_ { **size** } **number** is { 89 , 76 , 45 , 92 , 67 , 12 , 99 } 
_number_ **temp**
 _number_ **x**

#### for ( **x** is 0 , **x** smaller than **size** , **x** is **x** plus 1)
--
	[ printdown **number** { **x** } ]
__

[ printdown "" ]
[ printdown "" ]

#### for ( _number_ **i** is **size** minus 1 , **i** larger than 0 , **i** is **i** minus 1 )
--
	#### for ( _number_ **j** is 0 , **j** like or smaller than  **i** minus 1, **j** is **j** plus 1 )
	--
		#### if ( **number** { **j** } larger than **number** { **j**  plus 1 } )
		--
			**temp** is **number** { **j** }
			**number** { **j** } is **number** { **j** plus 1 }
			**number** { **j** plus 1 } is **temp**
		__
	__
__



#### for ( **x** is 0 , **x** smaller than **size** , **x** is **x** plus 1)
--
	[ printdown **number** { **x** } ]
__
