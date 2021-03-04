
enum bestillingsType{opp, inn, ned};

struct bestilling
{
    int etasje;                 // Etasje heisen skal til
    enum bestillingsType type;  // Knapptypen, enten er knappen fra heispanelet, eller så er det utenfra med et ønske om enten opp eller ned

};

struct bestilling bestillingsKø[10] = { 0 };

void checkForOrders();

void leggTilBestilling(struct bestilling nyBestilling);

bool bestillingFraHeispanel(struct bestilling panelBestilling);

int returnerAntallBestillinger();

bool orderFound();