#pragma once

namespace RAII
{
    template <typename Provider>
    class Booking
    {
    public:
        using BookingId = int;

        Booking(Provider *provider, const BookingId &booking_id) : provider_(provider), booking_id_(booking_id) {}
        Booking(const Booking &) = delete;
        Booking(Booking &&other) : provider_(other.provider_), booking_id_(other.booking_id_) { other.provider_ = nullptr; }
        Booking &operator=(const Booking &) = delete;
        Booking &operator=(Booking &&other)
        {
            delete provider_;
            provider_ = other.provider_;
            other.provider_ = nullptr;
            return *this;
        }
        ~Booking()
        {
            if (provider_ != nullptr)
            {
                provider_->CancelOrComplete(*this);
            }
        }

    private:
        Provider *provider_;
        BookingId booking_id_;
    };
}

// namespace RAII
// {
//     template <typename Provider>
//     class Booking
//     {
//     private:
//         using BookingId = typename Provider::BookingId;

//         Provider *provider;
//         BookingId booking_id;

//     public:
//         Booking(Provider *p, const BookingId &id)
//             : provider(p),
//               booking_id(id)
//         {
//         }

//         Booking(const Booking &) = delete;

//         Booking(Booking &&other)
//             : provider(other.provider),
//               booking_id(other.booking_id)
//         {
//             other.provider = nullptr;
//         }

//         Booking &operator=(const Booking &) = delete;

//         Booking &operator=(Booking &&other)
//         {
//             std::swap(provider, other.provider);
//             std::swap(booking_id, other.booking_id);
//             return *this;
//         }

//         BookingId GetId() const
//         {
//             return booking_id;
//         }

//         ~Booking()
//         {
//             if (provider != nullptr)
//             {
//                 provider->CancelOrComplete(*this);
//             }
//         }
//     };
// }
