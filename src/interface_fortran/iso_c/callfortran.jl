
# https://docs.julialang.org/en/v1/manual/calling-c-and-fortran-code/#Passing-Pointers-for-Modifying-Inputs-1

# Fortran passes all the arguments by reference, so we have to
# use references of the appropriate type.
v = Ref{Clonglong}(2)

# We are calling a subroutine, so return type is
# Void (for Fortran)  → Cvoid (via iso_c_binding) → nothing (via Base.cconvert)
@static if VERSION >= v"1.5.0"  # clearer syntax

   const FORTLIB = "fortranlib.so"
   @ccall FORTLIB.mypow(v::Ref{Clonglong})::Cvoid
else # works anyway

   # Argument types are specified with a tuple,
   # (Any,) isa Tuple => true
   # (Any)  isa Tuple => false
   ccall( (:mypow, "fortranlib.so"), Cvoid, (Ref{Clonglong},), v )
end

# The content reference is accessed with []
@assert v[] == 4
println("Four = ",v[])
