
using Formatting: printfmt
using LinearAlgebra
using DelimitedFiles

# Adapted from supplementary routines for the book
# "Spectral methods in Chemistry and Physics"

import SciAlgs.NumQuad: discrete_stieltjes, golub_welsch

function multiexpαβ(N)
  f(r)  = log(r)^2
  rmin = 0
  rmax = 1
  npts = 1000 - round(Int,500*((20-N)/20)) # minimum effort (ad hoc)
  nint = npts
  α, β, h = discrete_stieltjes(f,N,rmin,rmax,nint,npts)
  writedlm("multiexp_alpha_beta.mat",[α β])
  writedlm("multiexp_h.mat",h)
end

function multiexp(N)
  @assert N <= 100
  if !isfile("multiexp_alpha_beta.mat")
    @error("No precomputed α and β coeffs!")
  end
  αβ = readdlm("multiexp_alpha_beta.mat")
  α = αβ[1:N,1]
  β = αβ[1:N,2]
  h = readdlm("multiexp_h.mat")[1]
  λ, wt = golub_welsch(α,β,h)
end

function multiexpfull(N)
  f(r)  = log(r)^2
  rmin = 0
  rmax = 1
  npts = 1000 - round(Int,500*((20-N)/20)) # minimum effort (ad hoc)
  nint = npts
  α, β, h  = discrete_stieltjes(f,N,rmin,rmax,nint,npts)
  λ, wt = golub_welsch(α,β,h)
end


function test_multiexp()
   # Taken from Table 1 of 10.1002/jcc.10211
   # Also https://rsc.anu.edu.au/~pgill/multiexp.php?n=5
   eps = 1e-8
   println("Testing nquad=1")
   r,w = multiexp(1)
   @assert isapprox(r[1],0.1250000000,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[1],2.0000000000,atol=eps)
   println("Testing nquad=2")
   r,w = multiexp(2)
   @assert isapprox(r[1],0.0598509925,atol=eps)
   @assert isapprox(r[2],0.4536625210,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[1],1.6691361082,atol=eps)
   @assert isapprox(w[2],0.3308638918,atol=eps)
   println("Testing nquad=3")
   r,w = multiexp(3)
   @assert isapprox(r[1],0.0362633111,atol=eps)
   @assert isapprox(r[2],0.2731486024,atol=eps)
   @assert isapprox(r[3],0.6537110896,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[1],1.3638303836,atol=eps)
   @assert isapprox(w[2],0.5658154596,atol=eps)
   @assert isapprox(w[3],0.0703541567,atol=eps)
   println("Testing nquad=4")
   r,w = multiexp(4)
   @assert isapprox(r[1],0.0246451318,atol=eps)
   @assert isapprox(r[2],0.1831933310,atol=eps)
   @assert isapprox(r[3],0.4610171077,atol=eps)
   @assert isapprox(r[4],0.7655906466,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[1],1.1330156422,atol=eps)
   @assert isapprox(w[2],0.6612166786,atol=eps)
   @assert isapprox(w[3],0.1857929500,atol=eps)
   @assert isapprox(w[4],0.0199747293,atol=eps)
   println("Testing nquad=5")
   r,w = multiexp(5)
   @assert isapprox(r[1],0.0179624485,atol=eps)
   @assert isapprox(r[2],0.1317184306,atol=eps)
   @assert isapprox(r[3],0.3395971926,atol=eps)
   @assert isapprox(r[4],0.5945982935,atol=eps)
   @assert isapprox(r[5],0.8320575996,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[1],0.9588537970,atol=eps)
   @assert isapprox(w[2],0.6830020585,atol=eps)
   @assert isapprox(w[3],0.2815660272,atol=eps)
   @assert isapprox(w[4],0.0695856412,atol=eps)
   @assert isapprox(w[5],0.0069924762,atol=eps)
   println("Testing nquad=6")
   r,w = multiexp(6)
   @assert isapprox(r[1],0.0137303290,atol=eps)
   @assert isapprox(r[2],0.0994431475,atol=eps)
   @assert isapprox(r[3],0.2596678762,atol=eps)
   @assert isapprox(r[4],0.4685229897,atol=eps)
   @assert isapprox(r[5],0.6874245835,atol=eps)
   @assert isapprox(r[6],0.8742037763,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[1],0.8247373524,atol=eps)
   @assert isapprox(w[2],0.6701662035,atol=eps)
   @assert isapprox(w[3],0.3457959549,atol=eps)
   @assert isapprox(w[4],0.1269936018,atol=eps)
   @assert isapprox(w[5],0.0294555188,atol=eps)
   @assert isapprox(w[6],0.0028513686,atol=eps)
   println("Testing nquad=8")
   r,w = multiexp(8)
   @assert isapprox(r[1],0.0088308098,atol=eps)
   @assert isapprox(r[2],0.0626470137,atol=eps)
   @assert isapprox(r[3],0.1653937470,atol=eps)
   @assert isapprox(r[4],0.3076475309,atol=eps)
   @assert isapprox(r[5],0.4738811643,atol=eps)
   @assert isapprox(r[6],0.6449256028,atol=eps)
   @assert isapprox(r[7],0.8005576159,atol=eps)
   @assert isapprox(r[8],0.9222020825,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[1],0.6343476124,atol=eps)
   @assert isapprox(w[2],0.6078905783,atol=eps)
   @assert isapprox(w[3],0.4036485580,atol=eps)
   @assert isapprox(w[4],0.2184654657,atol=eps)
   @assert isapprox(w[5],0.0959319490,atol=eps)
   @assert isapprox(w[6],0.0320637571,atol=eps)
   @assert isapprox(w[7],0.0069997943,atol=eps)
   @assert isapprox(w[8],0.0006522851,atol=eps)
   println("Testing nquad=10")
   r,w = multiexp(10)
   @assert isapprox(r[ 1],0.0061869147,atol=eps)
   @assert isapprox(r[ 2],0.0431849645,atol=eps)
   @assert isapprox(r[ 3],0.1143932978,atol=eps)
   @assert isapprox(r[ 4],0.2157443263,atol=eps)
   @assert isapprox(r[ 5],0.3400163758,atol=eps)
   @assert isapprox(r[ 6],0.4777530668,atol=eps)
   @assert isapprox(r[ 7],0.6181540046,atol=eps)
   @assert isapprox(r[ 8],0.7500277506,atol=eps)
   @assert isapprox(r[ 9],0.8627655156,atol=eps)
   @assert isapprox(r[10],0.9472975116,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[ 1],0.5075100632,atol=eps)
   @assert isapprox(w[ 2],0.5377370883,atol=eps)
   @assert isapprox(w[ 3],0.4101581499,atol=eps)
   @assert isapprox(w[ 4],0.2686821571,atol=eps)
   @assert isapprox(w[ 5],0.1544536152,atol=eps)
   @assert isapprox(w[ 6],0.0768964762,atol=eps)
   @assert isapprox(w[ 7],0.0319269841,atol=eps)
   @assert isapprox(w[ 8],0.0102578456,atol=eps)
   @assert isapprox(w[ 9],0.0021782820,atol=eps)
   @assert isapprox(w[10],0.0001993384,atol=eps)
   println("Testing nquad=15")
   r,w = multiexp(15)
   @assert isapprox(r[ 1],0.0031568454,atol=eps)
   @assert isapprox(r[ 2],0.0214217428,atol=eps)
   @assert isapprox(r[ 3],0.0567152146,atol=eps)
   @assert isapprox(r[ 4],0.1082790024,atol=eps)
   @assert isapprox(r[ 5],0.1744898369,atol=eps)
   @assert isapprox(r[ 6],0.2530501060,atol=eps)
   @assert isapprox(r[ 7],0.3411169468,atol=eps)
   @assert isapprox(r[ 8],0.4354309056,atol=eps)
   @assert isapprox(r[ 9],0.5324530702,atol=eps)
   @assert isapprox(r[10],0.6285097879,atol=eps)
   @assert isapprox(r[11],0.7199410768,atol=eps)
   @assert isapprox(r[12],0.8032477673,atol=eps)
   @assert isapprox(r[13],0.8752323216,atol=eps)
   @assert isapprox(r[14],0.9331298792,atol=eps)
   @assert isapprox(r[15],0.9747402975,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[ 1],0.3253137565,atol=eps)
   @assert isapprox(w[ 2],0.3961243562,atol=eps)
   @assert isapprox(w[ 3],0.3593522229,atol=eps)
   @assert isapprox(w[ 4],0.2926536989,atol=eps)
   @assert isapprox(w[ 5],0.2219588508,atol=eps)
   @assert isapprox(w[ 6],0.1582926857,atol=eps)
   @assert isapprox(w[ 7],0.1061466261,atol=eps)
   @assert isapprox(w[ 8],0.0665501730,atol=eps)
   @assert isapprox(w[ 9],0.0385929320,atol=eps)
   @assert isapprox(w[10],0.0203475527,atol=eps)
   @assert isapprox(w[11],0.0094938596,atol=eps)
   @assert isapprox(w[12],0.0037511449,atol=eps)
   @assert isapprox(w[13],0.0011607732,atol=eps)
   @assert isapprox(w[14],0.0002398218,atol=eps)
   @assert isapprox(w[15],0.0000215456,atol=eps)
   println("Testing nquad=20")
   r,w = multiexp(20)
   @assert isapprox(r[ 1],0.0019241239,atol=eps)
   @assert isapprox(r[ 2],0.0128189043,atol=eps)
   @assert isapprox(r[ 3],0.0338360585,atol=eps)
   @assert isapprox(r[ 4],0.0647886177,atol=eps)
   @assert isapprox(r[ 5],0.1051527594,atol=eps)
   @assert isapprox(r[ 6],0.1541448603,atol=eps)
   @assert isapprox(r[ 7],0.2107591088,atol=eps)
   @assert isapprox(r[ 8],0.2737989508,atol=eps)
   @assert isapprox(r[ 9],0.3419087328,atol=eps)
   @assert isapprox(r[10],0.4136071132,atol=eps)
   @assert isapprox(r[11],0.4873224017,atol=eps)
   @assert isapprox(r[12],0.5614294486,atol=eps)
   @assert isapprox(r[13],0.6342874604,atol=eps)
   @assert isapprox(r[14],0.7042779985,atol=eps)
   @assert isapprox(r[15],0.7698423653,atol=eps)
   @assert isapprox(r[16],0.8295175821,atol=eps)
   @assert isapprox(r[17],0.8819702175,atol=eps)
   @assert isapprox(r[18],0.9260275322,atol=eps)
   @assert isapprox(r[19],0.9607063554,atol=eps)
   @assert isapprox(r[20],0.9852482390,atol=eps)
   @assert isapprox(sum(w),2.00000000,atol=eps)
   @assert isapprox(w[ 1],0.2308490189,atol=eps)
   @assert isapprox(w[ 2],0.3027886725,atol=eps)
   @assert isapprox(w[ 3],0.2986810329,atol=eps)
   @assert isapprox(w[ 4],0.2678766357,atol=eps)
   @assert isapprox(w[ 5],0.2274158666,atol=eps)
   @assert isapprox(w[ 6],0.1852655647,atol=eps)
   @assert isapprox(w[ 7],0.1455612505,atol=eps)
   @assert isapprox(w[ 8],0.1104305753,atol=eps)
   @assert isapprox(w[ 9],0.0808087449,atol=eps)
   @assert isapprox(w[10],0.0568766276,atol=eps)
   @assert isapprox(w[11],0.0383323430,atol=eps)
   @assert isapprox(w[12],0.0245782243,atol=eps)
   @assert isapprox(w[13],0.0148581882,atol=eps)
   @assert isapprox(w[14],0.0083614715,atol=eps)
   @assert isapprox(w[15],0.0043003770,atol=eps)
   @assert isapprox(w[16],0.0019659640,atol=eps)
   @assert isapprox(w[17],0.0007640520,atol=eps)
   @assert isapprox(w[18],0.0002333787,atol=eps)
   @assert isapprox(w[19],0.0000477502,atol=eps)
   @assert isapprox(w[20],0.0000042614,atol=eps)
end
