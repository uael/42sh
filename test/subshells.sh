(echo a;
(echo b))
(echo
(echo b))
(
    (echo a)
)
(
    (
        (
            (
                (
                    (
                        echo abc
                    )
                )
            )
        )
    )
)

(echo abc) | cd
(
    (echo abc)
) | echo | echo | echo | ls

FOO=BITE;(FOO=BAR; (FOO=BAZ; echo $FOO) | grep BAZ; echo $FOO | grep BAR)

