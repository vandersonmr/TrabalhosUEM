/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.HotelAnimais;

/**
 *
 * @author vanderson
 */
public class Acomodacao {

    private int num;
    private Porte dimensao;
    private AcomodacaoEstado estado = AcomodacaoEstado.Livre;
    private Estadia estadia = null;
    private Especie especie = Especie.Cachorro;
 

    public Acomodacao(int num, Porte dimensao, Especie especie) {
        this.especie = especie;
        this.num = num;
        this.dimensao = dimensao;
    }

    public Porte getDimensao() {
        return dimensao;
    }

    public void setDimensao(Porte dimensao) {
        this.dimensao = dimensao;
    }

    public AcomodacaoEstado getEstado() {
        return estado;
    }

    public int getNum() {
        return num;
    }

    public Estadia getEstadia() {
        return estadia;
    }

    public void addEstadia(Estadia estadia) {
        this.estadia = estadia;
        estado = AcomodacaoEstado.emUso;
    }

    public void sairEstadia() {
        this.estadia=null;
        estado=AcomodacaoEstado.Livre;
    }

    public Especie getEspecie() {
        return especie;
    }

    public void setEspecie(Especie especie) {
        this.especie = especie;
    }
     

}
