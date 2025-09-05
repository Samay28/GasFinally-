
#include "SlotWidget.h"

void USlotWidget::SetItemIcon(UTexture2D* NewIcon)
{
    if (ItemIcon && NewIcon)
    {
        ItemIcon->SetBrushFromTexture(NewIcon);
    }
}

void USlotWidget::setItemIconImage(UImage* img)
{
	ItemIcon = img;
}

void USlotWidget::setQuantityTextBlock(UTextBlock* txt)
{   
	QuantityText = txt;
}
