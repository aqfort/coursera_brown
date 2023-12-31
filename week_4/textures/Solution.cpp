#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
class Shape : public IShape
{
public:
    // Возвращает точную копию фигуры.
    // Если фигура содержит текстуру, то созданная копия содержит ту же самую
    // текстуру. Фигура и её копия совместно владеют этой текстурой.
    virtual std::unique_ptr<IShape> Clone() const = 0;

    virtual void SetPosition(Point position) final
    {
        position_ = std::move(position);
    }
    virtual Point GetPosition() const final
    {
        return position_;
    }

    virtual void SetSize(Size size) final
    {
        size_ = std::move(size);
    }
    virtual Size GetSize() const final
    {
        return size_;
    }

    virtual void SetTexture(std::shared_ptr<ITexture> texture) final
    {
        texture_ = std::move(texture);
    }
    virtual ITexture *GetTexture() const final
    {
        return texture_.get();
    }

    // Рисует фигуру на указанном изображении
    virtual void Draw(Image &image) const final
    {
        Point point;
        auto image_size = Size{
            .width = static_cast<int>(image.empty() ? false : image[0].size()),
            .height = static_cast<int>(image.size())};

        for (point.y = 0; point.y < size_.height; ++point.y)
        {
            for (point.x = 0; point.x < size_.width; ++point.x)
            {
                if (IsPointInShape(point))
                {
                    char pixel = '.';
                    if (texture_ && IsPointInSize(point, texture_->GetSize()))
                    {
                        pixel = texture_->GetImage()[point.y][point.x];
                    }
                    Point positioned_point = {point.x + position_.x, point.y + position_.y};
                    if (IsPointInSize(positioned_point, image_size))
                    {
                        image[positioned_point.y][positioned_point.x] = pixel;
                    }
                }
            }
        }
    }

private:
    virtual bool IsPointInShape(Point) const = 0;

    bool IsPointInSize(Point point, Size size) const
    {
        return point.x >= 0 && point.y >= 0 && point.x < size.width && point.y < size.height;
    }

    Point position_;
    Size size_;
    std::shared_ptr<ITexture> texture_;
};

class Rectangle : public Shape
{
public:
    virtual std::unique_ptr<IShape> Clone() const final
    {
        return std::make_unique<Rectangle>(*this);
    }

private:
    virtual bool IsPointInShape(Point) const final
    {
        return true;
    }
};

class Ellipse : public Shape
{
public:
    virtual std::unique_ptr<IShape> Clone() const final
    {
        return std::make_unique<Ellipse>(*this);
    }

private:
    virtual bool IsPointInShape(Point point) const final
    {
        return IsPointInEllipse(point, GetSize());
    }
};

// Напишите реализацию функции
std::unique_ptr<IShape> MakeShape(ShapeType shape_type)
{
    switch (shape_type)
    {
    case ShapeType::Rectangle:
        return std::make_unique<Rectangle>();
    case ShapeType::Ellipse:
        return std::make_unique<Ellipse>();
    }
    return nullptr;
}
