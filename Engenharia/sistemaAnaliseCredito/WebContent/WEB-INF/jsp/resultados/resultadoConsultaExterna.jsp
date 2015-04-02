<%-- 
    Document   : login.jsp
    Created on : 16/05/2013, 17:22:41
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
    <head>
        <style>
            @import url("/WEB-INF/style.css");
        </style>
        <style>
            .cabec {
                text-align: Right
            }

            .alertaNegocios {
                font-weight: bold;
                text-align: Center
            }

            .razaoSocial {
                font-size: 12pt;
                text-align: Center
            }

            .campos {
                text-align: right
            }

            .valorCampo {
                font-weight: bold;
            }

            .valorCampo1 {
                font-weight: bold;
                text-align: Center;
            }

            .mouseOverLink { background-color: #FFFFCC;
                             cursor: pointer;}

            td {font-size: 15pt;}

            .tblAlerta {
                BORDER-RIGHT: #ffc370 1px solid; 
                BORDER-TOP: #ffc370 1px solid; 
                FONT: 9px Verdana; 
                TEXT-TRANSFORM: none; 
                BORDER-LEFT: #ffc370 1px solid; 
                COLOR: #000000; 
                BORDER-BOTTOM: #ffc370 1px solid; 
                BACKGROUND-COLOR: #f9e7cf; 
                TEXT-DECORATION: none
            }

            .cordestaque1 {
                TEXT-DECORATION: none;
                COLOR: #000000; 
                FONT: 9px Verdana; 
                TEXT-TRANSFORM: none; 
                BACKGROUND-COLOR: #f9e7cf; 
            }

            .cordestaque2 {
                font-size: 9pt;
                text-transform: uppercase;
                font-weight: bold;	
                TEXT-TRANSFORM: none; 
                BACKGROUND-COLOR: #f0c284; 
            }


            .labelCreditRiskScoring {
                font-size:10pt;
            }

            .valorCreditRiskScoring {
                font-size:14pt;
            }

            .valorLimitePJFont1{
                font-size:14pt;
            }

            .valorLimitePJFont2{
                font-size:13pt;
            }
            .valorLimitePJFont3{
                font-size:12pt;
            }
            .valorLimitePJFont4{
                font-size:10pt;
            }
            .valorLimitePJFont5{
                font-size:8pt;
            }


        </style>

        <style media="screen">

            .exibir {display:inherit}
            .tamanhoTabela {width: 719px}
            .bordaTabela{}

            .sinalizadorLink {
                color: #ff0000;
                font-weight: bold; 
                font-size: 13px;
            }


        </style>

        <style media="print">

            .exibir {display:none}
            .tamanhoTabela {width: 100%}
            .bordaTabela{border:1px #000000 solid}

            .sinalizadorLink {
                display:none
            }  
        </style>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Sistema de Análise de Crédito</title>
    </head>
    <body>

        <form action="${pageContext.request.contextPath}/menu">
            <fieldset>
                <legend><h1>Análise servidor externo</h1></legend>
                <table class="tamanhoTabela" bgcolor="#F5F5F5" border="1" bordercolor="#FFFFFF" cellpadding="0" cellspacing="0" align="center">
                    <tbody><tr class="cor2">
                            <td class="titulo1" colspan="1" height="25" align="center">
                                <h2> Pendências Financeiras </h2>
                            </td>

                        </tr>
                        <tr class="cor6">
                            <td align="center">
                                <c:forEach items="${resultado.pendenciasFinanceiras}" var="pendencia">
                            <tr>
                                <td>${pendencia}</td>
                            </tr>
                        </c:forEach>
                        </td>
                        </tr>
                    </tbody>
                </table>

                <br>


                <table class="tamanhoTabela" bgcolor="#F5F5F5" border="1" bordercolor="#FFFFFF" cellpadding="0" cellspacing="0" align="center">
                    <tbody><tr>
                            <td>
                                <table class="tamanhoTabela" bgcolor="#F5F5F5" border="1" bordercolor="#FFFFFF" cellpadding="0" cellspacing="0"  align="center">
                                    <tbody><tr class="cor2">
                                            <td class="titulo1" height="25" align="center">
                                                <h2>Informações do Concentre</h2>
                                            </td>
                                        </tr>
                                        <tr class="cor6">
                                            <td align="center">
                                                <c:forEach items="${resultado.informaçõesDoConcentre}" var="pendencia">
                                            <tr>
                                                <td>${pendencia}</td>
                                            </tr>
                                        </c:forEach>
                                        </td>
                                        </tr>
                                    </tbody></table>
                            </td>
                        </tr>
                    </tbody></table>	
                <br>		   


                <br>										
                <table class="tamanhoTabela" bgcolor="#F5F5F5" border="1" bordercolor="#FFFFFF" cellpadding="0" cellspacing="0" align="center">
                    <tbody><tr class="cor2">
                            <td class="titulo1" height="25" align="center">

                                <h2>Informações do Recheque<br> (Cheques Extraviados/Sustados)</h2>
                            </td>
                        </tr>
                        <tr class="cor6">
                            <td align="center">
                                <c:forEach items="${resultado.informaçõesDoRecheque}" var="pendencia">
                            <tr>
                                <td>${pendencia}</td>
                            </tr>
                        </c:forEach>
                        </td>
                        </tr>
                    </tbody></table>


                <br>


                <input type="submit" onClick="window.history.back()" class="btn" value="Voltar"><br>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>
        </form>
    </body>
</html>


