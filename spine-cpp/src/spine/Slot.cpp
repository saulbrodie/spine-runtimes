#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/BaseSkeleton.h>

namespace spine {

Slot::Slot (SlotData *data, BaseSkeleton *skeleton, Bone *bone) :
				data(data),
				skeleton(skeleton),
				bone(bone),
				r(1),
				g(1),
				b(1),
				a(1),
				attachment(0) {
	if (!data) throw std::invalid_argument("data cannot be null.");
	if (!skeleton) throw std::invalid_argument("skeleton cannot be null.");
	if (!bone) throw std::invalid_argument("bone cannot be null.");
}

void Slot::setAttachment (Attachment *attachment) {
	this->attachment = attachment;
	attachmentTime = skeleton->time;
}

void Slot::setAttachmentTime (float time) {
	attachmentTime = skeleton->time - time;
}

float Slot::getAttachmentTime () const {
	return skeleton->time - attachmentTime;
}

void Slot::setToBindPose () {
	for (int i = 0, n = skeleton->slots.size(); i < n; i++) {
		if (this == skeleton->slots[i]) {
			setToBindPose(i);
			return;
		}
	}
}

void Slot::setToBindPose (int slotIndex) {
	r = data->r;
	g = data->g;
	b = data->b;
	a = data->a;
	setAttachment(data->attachmentName ? skeleton->getAttachment(slotIndex, *data->attachmentName) : 0);
}

} /* namespace spine */
