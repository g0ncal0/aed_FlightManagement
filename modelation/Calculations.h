//
// Created by Filipe Correia on 26/12/2023.
//

#ifndef AVIOES_CALCULATIONS_H
#define AVIOES_CALCULATIONS_H

class calculation{

public:
    static double toRadians(double degree) {
        return degree * (M_PI / 180.0);
    }

    static double calculateDistance(double lat1, double lon1, double lat2, double lon2) {

        const double earthRadius = 6371.0;

        // Convert latitude and longitude from degrees to radians
        lat1 = toRadians(lat1);
        lon1 = toRadians(lon1);
        lat2 = toRadians(lat2);
        lon2 = toRadians(lon2);

        // Calculate differences in coordinates
        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;

        // Haversine formula
        double a = std::sin(dlat / 2.0) * std::sin(dlat / 2.0) +
                   std::cos(lat1) * std::cos(lat2) *
                   std::sin(dlon / 2.0) * std::sin(dlon / 2.0);

        double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

        return earthRadius * c;
    }
};
#endif //AVIOES_CALCULATIONS_H
