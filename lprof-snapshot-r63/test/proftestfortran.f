c<html>
c<body>
c<pre>
      module global
      implicit none
      real a,b,s
c    a - one of the numbers to be added
c    b - the other number to be added
c    s  - the sum of a and b
      end module global
c
      program add2
c
 
      implicit none
c
c   use subroutine input to get the values for a and b
c<a name="call"><font color="FF0000">
      call input
c</font></a>
c
c    find the sum of and b 
c
      call add
c
c     use the subroutine output to send the results to the screen
c
      call output
      stop
      end
c
      subroutine add
      use global
      implicit none
c
c   Add two numbers and store the sum in "s"
c
      s = a + b
      return
      end
c
      subroutine input 
      use global
      implicit none
      print *, ' This program adds 2 real numbers'
      print *, ' Type them in now separated by a comma or space'
c
c   Now read the numbers that are typed by the user
c   this Fortran read will wait until the numbers are typed
c
      read *, a,b
      return
      end
c
      subroutine output
      use global
      implicit none
c
c   Print out the results with a description
c
      print *,  ' The sum of ', a,' and ' , b
      print *, ' is ' , s
      return
      end
c</pre>
c</body>
c</html>
