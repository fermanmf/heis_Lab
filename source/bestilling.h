
enum bestillingsType{opp, ned, inn};

struct bestilling
{
    int etasje;
    enum bestillingsType type;

};

struct bestilling bestillingsKø[10] = { 0 };

void leggTilBestilling(struct bestilling nyBestilling);

bool bestillingFraHeispanel(struct bestilling panelBestilling);

int returnerAntallBestillinger(struct bestilling kø);