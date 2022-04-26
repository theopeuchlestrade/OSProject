


// Fonction réalisant la suite de Syracuse à partir de l'entier n.
int funSyracuse(int n)
{
	float time = 0;
	int x = n;
	if (x % 2 == 0)
	{
		x = x / 2;
	}
	else if (x % 2 != 0)
	{
		x = 3 * x + 1;
	}
	else if (x == 0)
	{
		return time;
	}

    return  -1 ;
}

