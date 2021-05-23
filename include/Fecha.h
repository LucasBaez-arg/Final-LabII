#ifndef FECHA_H
#define FECHA_H
class Fecha
{
    public:
        /// METODOS
        Fecha();
        void FechaActual();

        virtual ~Fecha();

        /// SETTERS
        void SetDia(int x){dia=x;};
        void SetMes(int x){mes=x;};
        void SetAnnio(int x){annio=x;};
        /// GETTERS
        int GetDia(){return dia;};
        int GetMes(){return mes;};
        int GetAnnio(){return annio;};

    private:
        int dia;
        int mes;
        int annio;
};

#endif // FECHA_H
