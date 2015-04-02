/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Controle;

import DAOs.HistoricoDAO;
import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;
import gerenciadorCredito.LojistaSession;
import gerenciadorCredito.Model.ConsultaExternaDados;
import gerenciadorCredito.Model.*;
import java.util.Date;
import java.util.List;

/**
 *
 * @author vanderson
 */
@Resource
public class ResultadosController {

    private final Result result;
    private LojistaSession userSession;

    public ResultadosController(Result result, LojistaSession userSession) {
        this.result = result;
        this.userSession = userSession;
    }

    @Path("/resultadoMensagem")
    public void resultadoMensagem(String msg, int id) {
        Historico his = new Historico();
        his.setMsg(msg);
        his.setStatus(id);
        his.setUsuario(userSession.getUser().getEmail());
        his.setData(new Date());
        HistoricoDAO dao = new HistoricoDAO();
        dao.insert(his);
        dao.close();
    }

    @Path("/resultadoConsultaInterna")
    public void resultadoConsultaInterna() {
        Historico his = new Historico();
        his.setMsg("Consulta interna.");
        his.setStatus(11);
        his.setUsuario(userSession.getUser().getEmail());
        his.setData(new Date());
        HistoricoDAO dao = new HistoricoDAO();
        dao.insert(his);
        dao.close();

    }

    @Path("/resultadoConsultaExterna")
    public void resultadoConsultaExterna(ConsultaExternaDados consulta) {
        ConsultaExterna ce = new ConsultaExterna();
        ResultadoConsulta res = ce.colsutarExterna(consulta);
        
        if (res == null)
            result.redirectTo(MenuConsultaExternaController.class).menuConsultaExterna();

        Historico his = new Historico();
        his.setMsg("Consulta externa: " + consulta.getCpf());
        his.setStatus(10);
        his.setUsuario(userSession.getUser().getEmail());
        his.setData(new Date());
        HistoricoDAO dao = new HistoricoDAO();
        dao.insert(his);
        dao.close();

        result.include("resultado", res);
    }

    @Path("/resultadoRelatorio")
    public void resultadoRelatorio() {
        HistoricoDAO dao = new HistoricoDAO();
        List res = dao.getLasts();
        List res2 = dao.getEstatisticas();
        dao.close();
        result.include("resultado", res);
        result.include("resultado2", res2);
    }
}
