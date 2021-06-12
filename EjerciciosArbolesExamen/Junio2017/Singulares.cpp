//Nodos singulares --> la suma de sus descendientes = a la suma de sus antecesores
//Coste O(n) ya que reccore 1 vez los nodos del árbol
int singulares_aux(const Arbin<int>& a, int sumaAntecesores, int& cuentaSingular){
	if(a.esVacio()) return 0;
	int sumaDes = singulares_aux(a.hijoIz(),sumaAntecesores + a.raiz(), cuentaSingular) +
				singulares_aux(a.hijoDer(),sumaAntecesores + a.raiz(), cuentaSingular);
	if(sumaAntecesores == sumaDes) cuentaSingular++;
	
	return sumaDes+a.raiz();
}