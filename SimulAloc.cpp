struct SimulAloc{
  struct Noh{int ini; int tam; Noh *prox;};
  Noh *prim = nullptr;

  bool inicializar(int ini, int tam){
    if(prim != nullptr)
      return 1;
    prim = new Noh{ini, tam, nullptr};
    if(!prim)
      return 1;
    return 0;
  }

  int alocar(int tam){
    if(prim == nullptr)
      return -1;
    int addr = -1;
    Noh *tmp;
    if(prim->tam >= tam){
      addr = prim->ini + prim->tam - tam;
      prim->tam -= tam;
      if(prim->tam == 0){
        tmp = prim;
        prim = prim->prox;
        delete tmp;
      }
      return addr;
    }
    for(Noh *it = prim; it->prox != nullptr; it = it->prox){
      if(it->prox->tam >= tam){
        addr = it->prox->ini + it->prox->tam - tam;
        it->prox->tam -= tam;
        if(it->prox->tam == 0){
          tmp = it->prox;
          it->prox = tmp->prox;
          delete tmp;
        }
        return addr;
      }
    }
    return addr;
  }

  bool desalocar(int ini, int tam){
    if(prim == nullptr){
      prim = new Noh{ini, tam, nullptr};
      return 0;
    }
    Noh *tmp, *it;
    if(ini + tam < prim->ini){
      tmp = new Noh{ini, tam, prim};
      prim = tmp;
      return 0;
    }
    if(ini + tam == prim->ini){
      prim->ini = ini;
      prim->tam += tam;
      return 0;
    }
    for(it = prim; it->prox != nullptr; it = it->prox){
      if(it->ini + it->tam == ini && ini + tam == it->prox->ini){
        tmp = it->prox;
        it->tam += tam + tmp->tam;
        it->prox = tmp->prox;
        delete tmp;
        return 0;
      }
      if(it->ini + it->tam == ini && ini + tam < it->prox->ini){
        it->tam += tam;
        return 0;
      }
      if(it->ini + it->tam < ini && ini + tam == it->prox->ini){
        it->prox->ini = ini;
        it->prox->tam += tam;
        return 0;
      }
      if(it->ini + it->tam < ini && ini + tam < it->prox->ini){
        tmp = new Noh{ini, tam, it->prox};
        it->prox = tmp;
        return 0;
      }
    }

    if(it->ini + it->tam == ini){
      it->tam += tam;
      return 0;
    }
    if(it->ini + it->tam < ini){
      it->prox = new Noh{ini, tam, nullptr};
      return 0;
    }
    return 1;
  }

  void terminar(){
    Noh *tmp;
    while(prim != nullptr){
      tmp = prim;
      prim = prim->prox;
      delete tmp;
    }
  }
};
