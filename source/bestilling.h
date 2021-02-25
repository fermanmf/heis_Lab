
enum bestillingsType{opp, inn, ned};

struct bestilling
{
    int etasje;
    enum bestillingsType type;

};

struct bestilling bestillingsKø[10] = { 0 };

void checkForOrders();

void leggTilBestilling(struct bestilling nyBestilling);

bool bestillingFraHeispanel(struct bestilling panelBestilling);

int returnerAntallBestillinger();

bool orderFound();