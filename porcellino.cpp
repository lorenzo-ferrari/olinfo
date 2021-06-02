bool chiedi(int X);

int indovina()
{
  int k = 0;
  chiedi(0);
  for(int i = 0, test = 1; i < 31; i++, test <<= 1)
    if(chiedi(test<<1-1))
        k += test;

  return k;
}